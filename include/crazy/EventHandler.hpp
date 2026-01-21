#ifndef CRAZY_EVENT_HANDLER_HPP
#define CRAZY_EVENT_HANDLER_HPP

#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>

namespace crazy {

class Window;

/**
 * @brief Event types for the event system
 */
enum class EventType {
    KeyPress,
    KeyRelease,
    KeyRepeat,
    MouseButtonPress,
    MouseButtonRelease,
    MouseMove,
    WindowResize,
    WindowClose
};

/**
 * @brief Key event data structure
 */
struct KeyEvent {
    int key;
    int scancode;
    int mods;
};

/**
 * @brief Mouse button event data structure
 */
struct MouseButtonEvent {
    int button;
    int mods;
};

/**
 * @brief Mouse move event data structure
 */
struct MouseMoveEvent {
    double xpos;
    double ypos;
};

/**
 * @brief Window resize event data structure
 */
struct WindowResizeEvent {
    int width;
    int height;
};

/**
 * @brief Event handler class for managing input and window events
 * 
 * This class provides a callback-based event system for handling
 * keyboard, mouse, and window events using GLFW.
 * 
 * Example usage:
 * @code
 * EventHandler handler;
 * handler.setKeyPressCallback([](const KeyEvent& event) {
 *     if (event.key == GLFW_KEY_ESCAPE) {
 *         // Handle escape key
 *     }
 * });
 * handler.attachToWindow(window);
 * @endcode
 */
class EventHandler {
public:
    using KeyCallback = std::function<void(const KeyEvent&)>;
    using MouseButtonCallback = std::function<void(const MouseButtonEvent&)>;
    using MouseMoveCallback = std::function<void(const MouseMoveEvent&)>;
    using WindowResizeCallback = std::function<void(const WindowResizeEvent&)>;
    using WindowCloseCallback = std::function<void()>;
    
    /**
     * @brief Construct a new Event Handler object
     */
    EventHandler();
    
    /**
     * @brief Destroy the Event Handler object
     */
    ~EventHandler();
    
    /**
     * @brief Attach this event handler to a window
     * 
     * @param window Window to attach to
     */
    void attachToWindow(Window& window);
    
    /**
     * @brief Set the key press callback
     * 
     * @param callback Callback function for key press events
     */
    void setKeyPressCallback(KeyCallback callback);
    
    /**
     * @brief Set the key release callback
     * 
     * @param callback Callback function for key release events
     */
    void setKeyReleaseCallback(KeyCallback callback);
    
    /**
     * @brief Set the key repeat callback
     * 
     * @param callback Callback function for key repeat events
     */
    void setKeyRepeatCallback(KeyCallback callback);
    
    /**
     * @brief Set the mouse button press callback
     * 
     * @param callback Callback function for mouse button press events
     */
    void setMouseButtonPressCallback(MouseButtonCallback callback);
    
    /**
     * @brief Set the mouse button release callback
     * 
     * @param callback Callback function for mouse button release events
     */
    void setMouseButtonReleaseCallback(MouseButtonCallback callback);
    
    /**
     * @brief Set the mouse move callback
     * 
     * @param callback Callback function for mouse move events
     */
    void setMouseMoveCallback(MouseMoveCallback callback);
    
    /**
     * @brief Set the window resize callback
     * 
     * @param callback Callback function for window resize events
     */
    void setWindowResizeCallback(WindowResizeCallback callback);
    
    /**
     * @brief Set the window close callback
     * 
     * @param callback Callback function for window close events
     */
    void setWindowCloseCallback(WindowCloseCallback callback);
    
    /**
     * @brief Poll for events
     * 
     * This should be called once per frame to process pending events.
     */
    static void pollEvents();

private:
    // GLFW callback functions (static)
    static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void glfwWindowCloseCallback(GLFWwindow* window);
    
    // Event handler retrieval from window user pointer
    static EventHandler* getHandlerFromWindow(GLFWwindow* window);
    
    // Callback storage
    KeyCallback m_keyPressCallback;
    KeyCallback m_keyReleaseCallback;
    KeyCallback m_keyRepeatCallback;
    MouseButtonCallback m_mouseButtonPressCallback;
    MouseButtonCallback m_mouseButtonReleaseCallback;
    MouseMoveCallback m_mouseMoveCallback;
    WindowResizeCallback m_windowResizeCallback;
    WindowCloseCallback m_windowCloseCallback;
};

} // namespace crazy

#endif // CRAZY_EVENT_HANDLER_HPP
