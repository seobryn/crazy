#include "crazy/Window.hpp"
#include <iostream>

namespace crazy {

Window::Window(int width, int height, const std::string& title)
    : m_window(nullptr)
    , m_width(width)
    , m_height(height)
    , m_title(title)
{
    // Configure GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window: " << title << std::endl;
    }
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

Window::Window(Window&& other) noexcept
    : m_window(other.m_window)
    , m_width(other.m_width)
    , m_height(other.m_height)
    , m_title(std::move(other.m_title))
{
    other.m_window = nullptr;
}

Window& Window::operator=(Window&& other) noexcept {
    if (this != &other) {
        if (m_window) {
            glfwDestroyWindow(m_window);
        }
        
        m_window = other.m_window;
        m_width = other.m_width;
        m_height = other.m_height;
        m_title = std::move(other.m_title);
        
        other.m_window = nullptr;
    }
    return *this;
}

bool Window::isValid() const {
    return m_window != nullptr;
}

bool Window::shouldClose() const {
    return m_window && glfwWindowShouldClose(m_window);
}

void Window::setShouldClose(bool value) {
    if (m_window) {
        glfwSetWindowShouldClose(m_window, value ? GLFW_TRUE : GLFW_FALSE);
    }
}

void Window::makeContextCurrent() {
    if (m_window) {
        glfwMakeContextCurrent(m_window);
    }
}

void Window::swapBuffers() {
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}

int Window::getWidth() const {
    if (m_window) {
        int width;
        glfwGetFramebufferSize(m_window, &width, nullptr);
        return width;
    }
    return m_width;
}

int Window::getHeight() const {
    if (m_window) {
        int height;
        glfwGetFramebufferSize(m_window, nullptr, &height);
        return height;
    }
    return m_height;
}

GLFWwindow* Window::getNativeWindow() const {
    return m_window;
}

void Window::setTitle(const std::string& title) {
    m_title = title;
    if (m_window) {
        glfwSetWindowTitle(m_window, title.c_str());
    }
}

void Window::setVSync(bool enabled) {
    if (m_window) {
        glfwSwapInterval(enabled ? 1 : 0);
    }
}

} // namespace crazy
