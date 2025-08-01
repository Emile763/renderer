#include "Window.h"
#include "Shader.h"
#include "Cube.h"
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Object3D.h"
#include "Camera.h"
#include <cmath>

bool key_w = false;
bool key_a = false;
bool key_s = false;
bool key_d = false;
void keyCallback (GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_W:
            key_w = true;
            break;
        case GLFW_KEY_A:
            key_a = true;
            break;
        case GLFW_KEY_S:
            key_s = true;
            break;
        case GLFW_KEY_D:
            key_d = true;
            break;  
        default:
            break;
        }
    } else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_W:
            key_w = false;
            break;
        case GLFW_KEY_A:
            key_a = false;
            break;
        case GLFW_KEY_S:
            key_s = false;
            break;
        case GLFW_KEY_D:
            key_d = false;
            break;  
        default:
            break;
        }
    }
}

// to build : g++ main.cpp Window.cpp Shader.cpp Cube.cpp Vector.cpp Matrix.cpp MatrixUtils.cpp Object3D.cpp -lglfw -lGL -lGLEW -Wall -Wextra -pedantic-errors
int main() {
    srand(time(NULL));
    constexpr float PERIOD = 1.f / 60.f;
    constexpr auto  PERIOD_DURATION = std::chrono::round<std::chrono::nanoseconds>(std::chrono::duration<float>(PERIOD));
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr float PI = 3.1415926f;
    Window window(WIDTH, HEIGHT, "renderer");
    window.setBackgroundColor(Color{ 0.1f,0.1f,0.1f,1.0f });
    window.setKeyCallback(&keyCallback);
    const auto zero_time = std::chrono::high_resolution_clock::now();
    auto last_frame = zero_time;
    auto next_frame = last_frame + PERIOD_DURATION;

    Shader shader("./shaders/vertex.vs", "./shaders/fragment.fs");
    Cube cube;
    Object3D cubeObject;
    cubeObject.setPosition({0.f,0.f,-3.f});
    Camera camera(float(WIDTH) / float(HEIGHT), 1.f, 1000.f, 70.f);


    GLuint VAO_center;
    glCreateVertexArrays(1, &VAO_center);
    glBindVertexArray(VAO_center);
    GLuint VBO_center;
    glGenBuffers(1, &VBO_center);
    float center[] = {
        0.f, 0.f
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO_center);
    glBufferData(GL_ARRAY_BUFFER, sizeof(center), center, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint VAO_line;
    glCreateVertexArrays(1, &VAO_line);
    glBindVertexArray(VAO_line);
    GLuint VBO_line;
    glGenBuffers(1, &VBO_line);
    float line_size = 1.f;
    float line[] = {
        0.f,  0.f,
        0.f,  -0.1f
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    cubeObject.setShaderVariables();
    cubeObject.setPosition({0.f, 0.f, -3.f});
    camera.setShaderVariables();
    
    glLineWidth(5.f);
    glPointSize(10.f);
    const float speed = 5.f;
    while (!window.shouldClose())
    {
        
        std::this_thread::sleep_until(next_frame);
        next_frame += PERIOD_DURATION;
        auto this_frame = std::chrono::high_resolution_clock::now();
        // std::cout << "fps=" << 1.f/std::chrono::duration<float>(this_frame - last_frame).count() << "\n";
        last_frame = this_frame;
        
        float time_in_sec = std::chrono::duration<float>(this_frame - zero_time).count();
        Window::update();
        
        camera.setPosition({ 4 * std::cosf(time_in_sec), 0.f, 4* std::sinf(time_in_sec) });
        // Vec3 position  = camera.getPosition();
        // Vec3 dir       = {key_a * -1.f + key_d * 1.f,0.f,key_w * -1.f + key_s * 1.f};
        // dir.normalize();
        // Vec3 delta_pos = dir * PERIOD * speed;
        // Vec3 new_pos = position + delta_pos;
        // camera.setPosition(position + delta_pos);
        camera.LookAt(cubeObject.getPosition());
        window.beginDraw();
        shader.use();
        camera.setShaderVariables();

        cubeObject.setShaderVariables();
        window.draw(cube);

        float angle = camera.getRotation()[1];
        
        line[0] = -camera.getPosition()[0] / 15.f;
        line[1] = (camera.getPosition()[2] + 3.f) / 15.f;

        line[2] =  100.f * std::sinf(angle) / 15.f + line[0];
        line[3] =  100.f * (-std::cosf(angle)) / 15.f + line[1];
        glUseProgram(0);
        glBindVertexArray(VAO_center);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(VAO_line);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
        glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_LINES, 0, 2);

        window.endDraw();

    }


    return 0;
}