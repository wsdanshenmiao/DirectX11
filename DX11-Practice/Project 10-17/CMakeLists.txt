cmake_minimum_required(VERSION 3.14)

add_subdirectory("15_Geometry_Shader_Beginning")
add_subdirectory("16_Stream_Output")


if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Texture)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Texture DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Model)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Model DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
