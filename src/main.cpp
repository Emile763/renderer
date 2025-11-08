#include "Camera.h"
#include "Camera2D.h"
#include "CubeModel.h"
#include "DrawingQueue.h"
#include "Model.h"
#include "Object3D.h"
#include "Shader.h"
#include "Vector.h"
#include "Window.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include "RectangleModel.h"
#include "Texture.h"
#include "ShaderTextureParameter.h"
#include "ShaderParameterBundle.h"
#include "Object2D.h"

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
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr float PI = 3.1415926f;
    constexpr float mouse_sensibility = 0.008f;


    Window window(WIDTH, HEIGHT, "renderer");
    window.setBackgroundColor(Color{ 0.1f,0.1f,0.1f,1.0f });
    window.setVSync(false);


    Camera camera(float(WIDTH) / float(HEIGHT), 1.f, 1000.f, 70.f);

    const CubeModel& cube_model = CubeModel::getInstance();
    Model bocal_model("./models/bocal.obj");
    Model monkey_model("./models/monkey.obj");
    Object3D cube, bocal, monkey;
    cube.setPosition({ 0.f,0.f,-3.f });
    bocal.setPosition({ 3.f,0.f,0.f });
    monkey.setPosition({ -3.f,0.f,0.f });
    
    // Shader shader("./shaders/light_vertex.vs", "./shaders/light_fragment.fs");
    DrawingQueue drawing_queue;
    drawing_queue.addInitParameter(camera);
    drawing_queue.add(cube_model, cube);
    drawing_queue.add(bocal_model, bocal);
    drawing_queue.add(monkey_model, monkey);
   
    Shader texture3D_shader("./shaders/texture_light_vertex.vs", "./shaders/texture_light_fragment.fs");
    Model apple_model("./models/apple.obj");
    Object3D apple3D;
    apple3D.setPosition({ 0.f,0.f,3.f });
    Texture apple3D_texture("./textures/apple3D.png");
    ShaderTextureParameter apple3D_texture_parameter(apple3D_texture);
    ShaderParameterBundle apple3D_parameter_bundle;
    apple3D_parameter_bundle.add(apple3D);
    apple3D_parameter_bundle.add(apple3D_texture_parameter);
    DrawingQueue texture_drawing_queue(texture3D_shader);
    texture_drawing_queue.addInitParameter(camera);
    texture_drawing_queue.add(apple_model, apple3D_parameter_bundle);
    
    //--- Draw an Apple ---//
    // load the texture
    Texture apple_texture("./textures/apple.png");
    // Create a parameter to use the texture
    ShaderTextureParameter texture_parameter(apple_texture);
    // Create an Object to set the drawing size in pixel
    Object2D apple;
    apple.setScale({1.f, apple_texture.getHeight()/apple_texture.getWidth()});
    apple.setSize(0.1);
    // Create a bundle to group all the parameters
    ShaderParameterBundle apple_parameter_bundle;
    apple_parameter_bundle.add(texture_parameter);
    apple_parameter_bundle.add(apple);
    // Get the rectangle model. It will be used as a support for the drawing
    const RectangleModel& rectangle_model = RectangleModel::getInstance();
    
    // Create the 2D camera
    Camera2D camera2D(float(WIDTH)/HEIGHT);
    // Load the shader
    Shader shader2d("./shaders/2Dvertex.vs", "./shaders/2Dfragment.fs");
    // Create a drawing queue for the 2D shader
    DrawingQueue drawing_queue_2D(shader2d);
    drawing_queue_2D.addInitParameter(camera2D);
    // add the model with the apple parameters to the drawing queue
    drawing_queue_2D.add(rectangle_model, apple_parameter_bundle);


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
    auto zero_frame = std::chrono::high_resolution_clock::now();
    auto last_frame = zero_frame;
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

        float t = (this_frame - zero_frame).count() * 1e-9;
        apple.setRotation(5*t);
        apple.setPosition( {10*cosf(t), 5*sinf(2*t)});
        /**********************/

        /***** Rendering *****/
        window.beginDraw();

        drawing_queue.draw();
        texture_drawing_queue.draw();
        drawing_queue_2D.draw();

        glBindVertexArray(VAO_center);
        glDrawArrays(GL_POINTS, 0, 1);

        window.endDraw();
        /*********************/

    }

    Shader::deleteDefault3DShader();
    return 0;
}