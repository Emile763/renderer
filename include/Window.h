#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include "Drawable.h"
// Has to be maintain on the main thread
struct Color
{
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    float alpha = 0.0f;
};


class Window
{
private:
    GLFWwindow *m_window;
    int m_width;
    int m_height;
    const std::string m_title;
    Color m_background_color;
    GLint m_draw_mode = GL_TRIANGLES;

    static int number_of_windows;
    static GLFWwindow* current_context_window;
    static bool drawing;

    void (*m_key_callback) (GLFWwindow* window, int key, int scancode, int action, int mods);
    // Return false if the window is already the current context window
    bool makeContextCurrent();

    // void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
    Window(const int& width, const int& height, const std::string title);
    ~Window();

    void setBackgroundColor(const Color& color);

    // update all the windows by handling the different events
    void static update();

    bool shouldClose();

    void beginDraw();

    void draw(const Drawable& drawable);

    void endDraw();

    void close();

    void setKeyCallback(void (*key_callback) (GLFWwindow* window, int key, int scancode, int action, int mods));
};
