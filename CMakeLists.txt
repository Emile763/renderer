cmake_minimum_required(VERSION 4.0.0)
project(Renderer LANGUAGES CXX)

# enable_testing()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(ONLY_LIBS "" ON)
add_subdirectory(third-party/glew)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# Needed because glfw doesn't work with wayland
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
add_subdirectory(third-party/glfw)

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
    src/Model.cpp
    )
file(COPY ./shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ./models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories("RendererApp" PRIVATE include)
target_link_libraries("RendererApp" glfw GL libglew_static)


