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
#include "Model.h"
#include <cmath>

class InputHandler : public IInputHandler {
public:
    bool key_w = false;
    bool key_a = false;
    bool key_s = false;
    bool key_d = false;
    bool key_escape = false;
    bool key_space = false;
    bool key_shift = false;

    void handleInput(Window& window, int key, int scancode, int action, int mods) override;

};
void InputHandler::handleInput(Window& window, int key, int scancode, int action, int mods) {
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
        case GLFW_KEY_LEFT_SHIFT:
            key_shift = true;
            break;
        case GLFW_KEY_ESCAPE:
            key_escape = true;
            break;
        case GLFW_KEY_SPACE:
            key_space = true;
            break;
        default:
            break;
        }
    }
    else if (action == GLFW_RELEASE)
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
        case GLFW_KEY_LEFT_SHIFT:
            key_shift = false;
            break;
        case GLFW_KEY_SPACE:
            key_space = false;
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
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 800;
    constexpr float PI = 3.1415926f;
    constexpr float mouse_sensibility = 0.1f;
    Window window(WIDTH, HEIGHT, "renderer");
    window.setBackgroundColor(Color{ 0.1f,0.1f,0.1f,1.0f });
    const auto zero_time = std::chrono::high_resolution_clock::now();
    auto last_frame = zero_time;
    auto next_frame = last_frame + PERIOD_DURATION;

    // Shader shader("./shaders/vertex.vs", "./shaders/fragment.fs");
    Shader shader("./shaders/light_vertex.vs", "./shaders/light_fragment.fs");
    Cube cube_model;
    Model bocal_model("./models/bocal.obj");
    Model monkey_model("./models/monkey.obj");
    Object3D cube1, cube2, bocal, monkey;
    cube1.setPosition({ 0.f,0.f,-3.f });
    cube2.setPosition({ 0.f,0.f,3.f });
    bocal.setPosition({ 3.f,0.f,0.f });
    monkey.setPosition({ -3.f,0.f,0.f });
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


    InputHandler input_handler;

    window.setInputHandler(input_handler);
    window.disableCursor();

    window.setMousePosition({ 0.f,0.f });

    // glLineWidth(5.f);
    // glPointSize(10.f);
    const float speed = 5.f;

    const float max_pitch_rotation = PI * 89.f / 180.f;
    while (!window.shouldClose())
    {

        std::this_thread::sleep_until(next_frame);
        next_frame += PERIOD_DURATION;
        auto this_frame = std::chrono::high_resolution_clock::now();
        // std::cout << "fps=" << 1.f/std::chrono::duration<float>(this_frame - last_frame).count() << "\n";
        last_frame = this_frame;

        float time_in_sec = std::chrono::duration<float>(this_frame - zero_time).count();
        Window::update();

        Vec2 mouse_pos = window.getMousePosition();
        window.setMousePosition({ 0.f,0.f });
        Vec3 camera_direction = camera.getDirection();
        Vec3 camera_direction2D = { camera_direction[0], 0.f, camera_direction[2] };
        camera_direction2D.normalize();
        Vec3 normal_camera_direction2D = { -camera_direction2D[2], 0.f, camera_direction2D[0] };

        Vec3 current_rotation = camera.getRotation();
        Vec3 new_rotation = current_rotation + Vec3{ mouse_pos[1], mouse_pos[0], 0.f } * mouse_sensibility * PERIOD;

        new_rotation[0] = std::min(new_rotation[0], max_pitch_rotation);
        new_rotation[0] = std::max(new_rotation[0], -max_pitch_rotation);

        camera.setRotation(new_rotation);

        Vec3 position = camera.getPosition();
        Vec3 moving_direction;

        if (input_handler.key_w)
            moving_direction += camera_direction2D;
        if (input_handler.key_s)
            moving_direction -= camera_direction2D;
        if (input_handler.key_d)
            moving_direction += normal_camera_direction2D;
        if (input_handler.key_a)
            moving_direction -= normal_camera_direction2D;
        moving_direction.normalize();

        // std::cout << "camera_direction: " << camera_direction2D[0] << " " << camera_direction2D[2] << "\n";
        // std::cout << "moving_direction: " << moving_direction[0] << " " << moving_direction[2] << "\n";
        Vec3 delta_pos = moving_direction * PERIOD * speed;
        if(input_handler.key_space)
            delta_pos[1] += PERIOD * speed;
        if(input_handler.key_shift)
            delta_pos[1] -= PERIOD * speed;
        Vec3 new_pos = position + delta_pos;
        camera.setPosition(position + delta_pos);


        // camera.LookAt(cube1.getPosition());
        window.beginDraw();
        shader.use();
        camera.setShaderVariables();

        cube1.setShaderVariables();
        window.draw(cube_model);

        cube2.setShaderVariables();
        window.draw(cube_model);

        bocal.setShaderVariables();
        window.draw(bocal_model);

        monkey.setShaderVariables();
        window.draw(monkey_model);

        float angle = camera.getRotation()[1];

        line[0] = -camera.getPosition()[0] / 15.f;
        line[1] = (camera.getPosition()[2]) / 15.f;

        line[2] = line[0] - camera_direction2D[0];
        line[3] = line[1] + camera_direction2D[2];
        glUseProgram(0);
        glBindVertexArray(VAO_center);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(VAO_line);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
        glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);
        // glDrawArrays(GL_LINES, 0, 2);

        window.endDraw();
        if (input_handler.key_escape)
            window.close();

    }


    return 0;
}