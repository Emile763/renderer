cmake_minimum_required(VERSION 4.0.0)
project(Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

option(ONLY_LIBS "" ON)
add_subdirectory(third-party/glew)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# Needed because glfw doesn't work with wayland
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
add_subdirectory(third-party/glfw)

add_executable("RendererApp" 
    src/camera/Camera.cpp
    src/camera/Camera2D.cpp
    src/drawing/DrawingQueue.cpp
    src/drawing/model/CubeModel.cpp
    src/drawing/model/Model.cpp
    src/drawing/model/RectangleModel.cpp
    src/main.cpp
    src/math/MatrixUtils.cpp
    src/math/Vector.cpp
    src/movable/Movable2D.cpp
    src/movable/Movable3D.cpp
    src/shader/parameter/empty/EmptyShaderParameter.cpp
    src/shader/parameter/movable/Object2D.cpp
    src/shader/parameter/movable/Object3D.cpp
    src/shader/parameter/ShaderParameterBundle.cpp
    src/shader/parameter/texture/ShaderTextureParameter.cpp
    src/shader/Shader.cpp
    src/texture/Texture.cpp
    src/window/Window.cpp
    third-party/stb/src/stb_image.cpp
    )
file(COPY ./shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ./models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ./textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories("RendererApp" PRIVATE include)
target_include_directories("RendererApp" PRIVATE include/camera)
target_include_directories("RendererApp" PRIVATE include/drawing)
target_include_directories("RendererApp" PRIVATE include/drawing/model)
target_include_directories("RendererApp" PRIVATE include/math)
target_include_directories("RendererApp" PRIVATE include/movable)
target_include_directories("RendererApp" PRIVATE include/shader)
target_include_directories("RendererApp" PRIVATE include/shader/parameter)
target_include_directories("RendererApp" PRIVATE include/shader/parameter/empty)
target_include_directories("RendererApp" PRIVATE include/shader/parameter/movable)
target_include_directories("RendererApp" PRIVATE include/shader/parameter/texture)
target_include_directories("RendererApp" PRIVATE include/texture)
target_include_directories("RendererApp" PRIVATE include/window)
target_include_directories("RendererApp" PRIVATE third-party/stb/include)
target_link_libraries("RendererApp" glfw GL libglew_static)


