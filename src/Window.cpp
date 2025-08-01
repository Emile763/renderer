#include "Window.h"
#include <iostream>

#include <assert.h>
// Static Members Initialization
int Window::number_of_windows = 0;
GLFWwindow *Window::current_context_window = NULL;
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



Window::Window(const int &width, const int &height, const std::string title)
    : m_width(width), m_height(height), m_title(title), m_background_color(Color())
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapInterval(0);
    number_of_windows++;
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

void Window::setBackgroundColor(const Color &color)
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
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::endDraw()
{
    glfwSwapBuffers(m_window);
    drawing = false;
}

void Window::draw(const Drawable &drawable)
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

void Window::setKeyCallback(void(*key_callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
{
    glfwSetKeyCallback(m_window, key_callback);
}
