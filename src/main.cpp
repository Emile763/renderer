#include "Camera.h"
#include "Cube.h"
#include "DrawingQueue.h"
#include "Matrix.h"
#include "Model.h"
#include "Object3D.h"
#include "Shader.h"
#include "Vector.h"
#include "Window.h"
#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

class InputHandler : public IInputHandler {
public:
    bool key_w = false;
    bool key_a = false;
    bool key_s = false;
    bool key_d = false;
    bool key_e = false;
    bool key_escape = false;
    bool key_space = false;
    bool key_shift = false;

    void handleInput(Window& window, int key, int scancode, int action, int mods) override;

};



void InputHandler::handleInput(Window& window, int key, int scancode, int action, int mods) {
    // unused parameters
    (void)window;
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_E:
            key_e = true;
            break;
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
        case GLFW_KEY_E:
            key_e = false;
            break;
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

class FocusHandler : public IFocusHandler {
public:
    void handleFocus(Window& window, bool focused) override;
};

void FocusHandler::handleFocus(Window& window, bool focused) {
    // unused parameters
    (void)window;
    std::cout << "focused --> " << focused << std::endl;
}

int main() {
    srand(time(NULL));
    constexpr float PERIOD = 1.f / 60.f;
    constexpr auto  PERIOD_DURATION = std::chrono::round<std::chrono::nanoseconds>(std::chrono::duration<float>(PERIOD));
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 800;
    constexpr float PI = 3.1415926f;
    constexpr float mouse_sensibility = 0.008f;


    Window window(WIDTH, HEIGHT, "renderer");
    window.setBackgroundColor(Color{ 0.1f,0.1f,0.1f,1.0f });
    window.setVSync(false);


    Camera camera(float(WIDTH) / float(HEIGHT), 1.f, 1000.f, 70.f);

    const Cube& cube_model = Cube::getInstance();
    Model bocal_model("./models/bocal.obj");
    Model monkey_model("./models/monkey.obj");
    Object3D cube1, cube2, bocal, monkey;
    cube1.setPosition({ 0.f,0.f,-3.f });
    cube2.setPosition({ 0.f,0.f,3.f });
    bocal.setPosition({ 3.f,0.f,0.f });
    monkey.setPosition({ -3.f,0.f,0.f });

    // Shader shader("./shaders/light_vertex.vs", "./shaders/light_fragment.fs");
    DrawingQueue drawing_queue;
    drawing_queue.addInitParameter(camera);
    drawing_queue.add(cube_model, cube1);
    drawing_queue.add(cube_model, cube2);
    drawing_queue.add(bocal_model, bocal);
    drawing_queue.add(monkey_model, monkey);

    // Crosshair
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


    InputHandler input_handler;
    FocusHandler focus_handler;
    window.setInputHandler(&input_handler);
    window.setFocusHandler(&focus_handler);
    window.disableCursor();


    const float speed = 5.f;
    const float max_pitch_rotation = PI * 89.f / 180.f;
    auto last_frame = std::chrono::high_resolution_clock::now();
    auto next_frame = last_frame + PERIOD_DURATION;
    while (!window.shouldClose())
    {

        std::this_thread::sleep_until(next_frame);
        next_frame += PERIOD_DURATION;
        auto this_frame = std::chrono::high_resolution_clock::now();
        last_frame = this_frame;

        Window::update();

        /***  Handle Inputs ***/

        if (input_handler.key_escape)
        {
            window.close();
            break;
        }

        Vec2 mouse_pos = window.getMousePosition();
        window.setMousePosition({ 0.f,0.f });

        Vec3 camera_direction = camera.getDirection();
        Vec3 camera_direction2D = { camera_direction[0], 0.f, camera_direction[2] };
        camera_direction2D.normalize();
        Vec3 normal_camera_direction2D = { -camera_direction2D[2], 0.f, camera_direction2D[0] };

        Vec3 new_rotation = camera.getRotation() + Vec3{ mouse_pos[1], mouse_pos[0], 0.f } * mouse_sensibility;

        new_rotation[0] = std::min(new_rotation[0], max_pitch_rotation);
        new_rotation[0] = std::max(new_rotation[0], -max_pitch_rotation);

        camera.setRotation(new_rotation);

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

        Vec3 delta_pos = moving_direction * PERIOD * speed;
        if (input_handler.key_space)
            delta_pos[1] += PERIOD * speed;
        if (input_handler.key_shift)
            delta_pos[1] -= PERIOD * speed;

        Vec3 new_pos = camera.getPosition() + delta_pos;
        camera.setPosition(new_pos);

        /**********************/

        /***** Rendering *****/
        window.beginDraw();

        drawing_queue.draw();

        glBindVertexArray(VAO_center);
        glDrawArrays(GL_POINTS, 0, 1);

        window.endDraw();
        /*********************/

    }


    return 0;
}