#ifndef CRAZY_WINDOW_HPP
#define CRAZY_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace crazy {

/**
 * @brief Window wrapper class for GLFW window management
 * 
 * This class provides a C++ wrapper around GLFW window functionality,
 * handling window creation, destruction, and basic window operations.
 * 
 * Example usage:
 * @code
 * crazy::Window window(800, 600, "My App");
 * if (!window.isValid()) {
 *     // Handle error
 * }
 * @endcode
 */
class Window {
public:
    /**
     * @brief Construct a new Window object
     * 
     * @param width Window width in pixels
     * @param height Window height in pixels
     * @param title Window title
     */
    Window(int width, int height, const std::string& title);
    
    /**
     * @brief Destroy the Window object
     */
    ~Window();
    
    // Disable copy construction and assignment
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    
    // Enable move construction and assignment
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;
    
    /**
     * @brief Check if the window was created successfully
     * 
     * @return true if window is valid
     * @return false if window creation failed
     */
    bool isValid() const;
    
    /**
     * @brief Check if the window should close
     * 
     * @return true if window should close
     * @return false otherwise
     */
    bool shouldClose() const;
    
    /**
     * @brief Set the window should close flag
     * 
     * @param value true to request window close
     */
    void setShouldClose(bool value);
    
    /**
     * @brief Make the window's OpenGL context current
     */
    void makeContextCurrent();
    
    /**
     * @brief Swap the front and back buffers
     */
    void swapBuffers();
    
    /**
     * @brief Get the window width
     * 
     * @return int Window width in pixels
     */
    int getWidth() const;
    
    /**
     * @brief Get the window height
     * 
     * @return int Window height in pixels
     */
    int getHeight() const;
    
    /**
     * @brief Get the raw GLFW window pointer
     * 
     * @return GLFWwindow* Raw window pointer
     */
    GLFWwindow* getNativeWindow() const;
    
    /**
     * @brief Set the window title
     * 
     * @param title New window title
     */
    void setTitle(const std::string& title);
    
    /**
     * @brief Enable or disable VSync
     * 
     * @param enabled true to enable VSync, false to disable
     */
    void setVSync(bool enabled);

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
};

} // namespace crazy

#endif // CRAZY_WINDOW_HPP
