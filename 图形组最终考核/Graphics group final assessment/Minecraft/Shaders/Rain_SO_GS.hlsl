#include "Particle.hlsli"

[maxvertexcount(6)]
void GS(point VertexParticle gIn[1], inout PointStream<VertexParticle> output)
{
    gIn[0].age += g_TimeStep;
    
    if (gIn[0].type == PT_EMITTER)
    {
        // 是否到时间发射新的粒子
        if (gIn[0].age > g_EmitInterval)
        {
            [unroll]
            for (int i = 0; i < 5; ++i)
            {
                // 在摄像机上方的区域让雨滴降落
                float3 vRandom = 30.0f * RandVec3((float) i / 5.0f);
                vRandom.y = 20.0f;
                
                VertexParticle p;
                p.initialPosW = g_EmitPosW.xyz + vRandom;
                p.initialVelW = float3(0.0f, 0.0f, 0.0f);
                p.sizeW = float2(1.0f, 1.0f);
                p.age = 0.0f;
                p.type = PT_PARTICLE;
                
                output.Append(p);
            }
            
            // 重置时间准备下一次发射
            gIn[0].age = 0.0f;
        }
        
        // 总是保留发射器
        output.Append(gIn[0]);
    }
    else
    {
        // 用于限制粒子数目产生的特定条件，对于不同的粒子系统限制也有所变化
        if (gIn[0].age <= g_AliveTime)
            output.Append(gIn[0]);
    }
}
