#include "Window.h"
#include <iostream>

#include <assert.h>
// Static Members Initialization
int Window::number_of_windows = 0;
GLFWwindow* Window::current_context_window = NULL;
bool Window::drawing = false;

bool Window::makeContextCurrent()
{
    if (current_context_window != m_window)
    {
        glfwMakeContextCurrent(m_window);

        current_context_window = m_window;
        return true;
    }
    return false;
}




Window::Window(const int& width, const int& height, const std::string title)
    : m_width(width), m_height(height), m_title(title), m_background_color(Color()),
    m_input_handler(nullptr)
{
    if (!number_of_windows)
    {
        if (!glfwInit())
        {
            std::cerr << "Error While Initializing glfw\n";
            exit(EXIT_FAILURE);
        }
    }
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Error While Initializing glew: " << glewGetErrorString(err) << "\n";
        exit(EXIT_FAILURE);
    }
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(0);
    number_of_windows++;

    glfwSetWindowUserPointer(m_window, this);

}

Window::~Window()
{
    close();
    glfwDestroyWindow(m_window);
    number_of_windows--;
    if (!number_of_windows)
    {
        glfwTerminate();
    }
}

void Window::setBackgroundColor(const Color& color)
{
    assert(!drawing);
    m_background_color = color;
    if (current_context_window == m_window)
    {
        glClearColor(m_background_color.red, m_background_color.green, m_background_color.blue, m_background_color.alpha);
    }
}

void Window::update()
{
    glfwPollEvents();
}

bool Window::shouldClose()
{
    return (m_window == NULL) || glfwWindowShouldClose(m_window);
}

void Window::beginDraw()
{
    assert(!drawing);
    drawing = true;
    if (makeContextCurrent())
    {
        glClearColor(m_background_color.red, m_background_color.green, m_background_color.blue, m_background_color.alpha);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endDraw()
{
    glfwSwapBuffers(m_window);
    drawing = false;
}

void Window::draw(const IDrawable& drawable)
{
    glBindVertexArray(drawable.getVAO());
    glDrawArrays(m_draw_mode, 0, drawable.getVerticesNumber());
}

void Window::close()
{
    if (m_window != NULL)
    {
        if (current_context_window == m_window)
        {
            current_context_window = NULL;
        }
        glfwDestroyWindow(m_window);
    }
    m_window = NULL;
}

void Window::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* abstract_window = static_cast<Window*> (glfwGetWindowUserPointer(window));
    abstract_window->m_input_handler->handleInput(*abstract_window, key, scancode, action, mods);
}


void Window::setInputHandler(IInputHandler& input_handler)
{
    m_input_handler = &input_handler;
    glfwSetKeyCallback(m_window, &Window::keyCallBack);
}


void Window::disableCursor() {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Window::enableCursor() {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Vec2 Window::getMousePosition() const {
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    return Vec2{(float)x, (float)y};
}
void Window::setMousePosition(const Vec2& position) {
    glfwSetCursorPos(m_window, position[0], position[1]);
}