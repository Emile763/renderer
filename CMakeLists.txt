cmake_minimum_required(VERSION 4.0.0)
project(Renderer LANGUAGES CXX)

enable_testing()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable("RendererApp" 
    src/main.cpp
    src/Cube.cpp
    src/Matrix.cpp
    src/MatrixUtils.cpp
    src/Object3D.cpp
    src/Shader.cpp
    src/Vector.cpp
    src/Window.cpp
    src/Movable3D.cpp
    src/Camera.cpp
    )
file(COPY ./shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories("RendererApp" PRIVATE include)
target_link_libraries("RendererApp" glfw GL GLEW)


