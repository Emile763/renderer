#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include "IDrawable.h"
#include "IInputHandler.h"
#include "IFocusHandler.h"
#include "Vector.h"
#include "DrawingQueue.h"

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
    IInputHandler *m_input_handler;
    IFocusHandler *m_focus_handler;

    static int number_of_windows;
    static GLFWwindow* current_context_window;
    static bool drawing;

    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void focusCallBack(GLFWwindow* window, int focused);
    
    // Return false if the window is already the current context window
    bool makeContextCurrent();

public:
    // update all the windows by handling the different events
    void static update();

    Window(const int& width, const int& height, const std::string title);
    ~Window();

    void setBackgroundColor(const Color& color);

    void beginDraw();
    void endDraw();

    void setVSync(const bool& state);
    
    bool shouldClose();
    void close();

    void setInputHandler(IInputHandler *input_handler = nullptr);
    void setFocusHandler(IFocusHandler *focus_handler = nullptr);

    void disableCursor();
    void enableCursor();

    Vec2 getMousePosition() const;
    void setMousePosition(const Vec2 &position);

};
