#include "crazy/EventHandler.hpp"
#include "crazy/Window.hpp"

namespace crazy {

EventHandler::EventHandler()
    : m_keyPressCallback(nullptr)
    , m_keyReleaseCallback(nullptr)
    , m_keyRepeatCallback(nullptr)
    , m_mouseButtonPressCallback(nullptr)
    , m_mouseButtonReleaseCallback(nullptr)
    , m_mouseMoveCallback(nullptr)
    , m_windowResizeCallback(nullptr)
    , m_windowCloseCallback(nullptr)
{
}

EventHandler::~EventHandler() {
}

void EventHandler::attachToWindow(Window& window) {
    GLFWwindow* glfwWindow = window.getNativeWindow();
    if (glfwWindow) {
        // Store pointer to this EventHandler in the window's user pointer
        glfwSetWindowUserPointer(glfwWindow, this);
        
        // Set up GLFW callbacks
        glfwSetKeyCallback(glfwWindow, glfwKeyCallback);
        glfwSetMouseButtonCallback(glfwWindow, glfwMouseButtonCallback);
        glfwSetCursorPosCallback(glfwWindow, glfwCursorPosCallback);
        glfwSetFramebufferSizeCallback(glfwWindow, glfwFramebufferSizeCallback);
        glfwSetWindowCloseCallback(glfwWindow, glfwWindowCloseCallback);
    }
}

void EventHandler::setKeyPressCallback(KeyCallback callback) {
    m_keyPressCallback = callback;
}

void EventHandler::setKeyReleaseCallback(KeyCallback callback) {
    m_keyReleaseCallback = callback;
}

void EventHandler::setKeyRepeatCallback(KeyCallback callback) {
    m_keyRepeatCallback = callback;
}

void EventHandler::setMouseButtonPressCallback(MouseButtonCallback callback) {
    m_mouseButtonPressCallback = callback;
}

void EventHandler::setMouseButtonReleaseCallback(MouseButtonCallback callback) {
    m_mouseButtonReleaseCallback = callback;
}

void EventHandler::setMouseMoveCallback(MouseMoveCallback callback) {
    m_mouseMoveCallback = callback;
}

void EventHandler::setWindowResizeCallback(WindowResizeCallback callback) {
    m_windowResizeCallback = callback;
}

void EventHandler::setWindowCloseCallback(WindowCloseCallback callback) {
    m_windowCloseCallback = callback;
}

void EventHandler::pollEvents() {
    glfwPollEvents();
}

// Static GLFW callbacks
void EventHandler::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    EventHandler* handler = getHandlerFromWindow(window);
    if (!handler) return;
    
    KeyEvent event{key, scancode, mods};
    
    if (action == GLFW_PRESS && handler->m_keyPressCallback) {
        handler->m_keyPressCallback(event);
    } else if (action == GLFW_RELEASE && handler->m_keyReleaseCallback) {
        handler->m_keyReleaseCallback(event);
    } else if (action == GLFW_REPEAT && handler->m_keyRepeatCallback) {
        handler->m_keyRepeatCallback(event);
    }
}

void EventHandler::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    EventHandler* handler = getHandlerFromWindow(window);
    if (!handler) return;
    
    MouseButtonEvent event{button, mods};
    
    if (action == GLFW_PRESS && handler->m_mouseButtonPressCallback) {
        handler->m_mouseButtonPressCallback(event);
    } else if (action == GLFW_RELEASE && handler->m_mouseButtonReleaseCallback) {
        handler->m_mouseButtonReleaseCallback(event);
    }
}

void EventHandler::glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    EventHandler* handler = getHandlerFromWindow(window);
    if (!handler) return;
    
    if (handler->m_mouseMoveCallback) {
        MouseMoveEvent event{xpos, ypos};
        handler->m_mouseMoveCallback(event);
    }
}

void EventHandler::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    EventHandler* handler = getHandlerFromWindow(window);
    if (!handler) return;
    
    if (handler->m_windowResizeCallback) {
        WindowResizeEvent event{width, height};
        handler->m_windowResizeCallback(event);
    }
}

void EventHandler::glfwWindowCloseCallback(GLFWwindow* window) {
    EventHandler* handler = getHandlerFromWindow(window);
    if (!handler) return;
    
    if (handler->m_windowCloseCallback) {
        handler->m_windowCloseCallback();
    }
}

EventHandler* EventHandler::getHandlerFromWindow(GLFWwindow* window) {
    return static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
}

} // namespace crazy
