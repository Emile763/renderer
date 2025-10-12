#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include "IDrawable.h"
#include "IInputHandler.h"
#include "Vector.h"

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
    IInputHandler *m_input_handler;

    static int number_of_windows;
    static GLFWwindow* current_context_window;
    static bool drawing;

    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    // Return false if the window is already the current context window
    bool makeContextCurrent();

public:
    // update all the windows by handling the different events
    void static update();

    Window(const int& width, const int& height, const std::string title);
    ~Window();

    void setBackgroundColor(const Color& color);

    void beginDraw();
    void draw(const IDrawable& drawable);
    void endDraw();
    
    bool shouldClose();
    void close();

    void setInputHandler(IInputHandler &input_handler);

    void disableCursor();
    void enableCursor();

    Vec2 getMousePosition() const;
    void setMousePosition(const Vec2 &position);

};
