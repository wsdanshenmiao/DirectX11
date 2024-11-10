﻿#pragma once
#ifndef __D3DUTIL__H__
#define __D3DUTIL__H__

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <d3d12shader.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <vector>
#include <array>
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <comdef.h>
#include "d3dx12.h"

namespace DSM {

	class D3DUtil
	{
	public:
		template <class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		static ComPtr<ID3D12Resource> CreateDefaultBuffer(
			ID3D12Device* device,
			ID3D12GraphicsCommandList* cmdList,
			const void* initData,
			UINT64 byteSize,
			ComPtr<ID3D12Resource>& upLoadBuffer);

		static UINT CalcConstantBufferByteSize(UINT byteSize) noexcept;

		static ComPtr<ID3DBlob> CompileShader(
			const WCHAR* fileName,
			const D3D_SHADER_MACRO* defines,
			const std::string& enteryPoint,
			const std::string& target,
			const WCHAR* outputFileName = nullptr);
	};

	class DxException
	{
	public:
		DxException() = default;
		DxException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

		std::wstring ToString()const;

		HRESULT ErrorCode = S_OK;
		std::wstring FunctionName;
		std::wstring Filename;
		int LineNumber = -1;
	};

	inline std::wstring AnsiToWString(const std::string& str)
	{
		WCHAR buffer[512];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
		return std::wstring(buffer);
	}

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}
#endif

}


#endif // !__D3DUTIL__H__

