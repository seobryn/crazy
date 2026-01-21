#ifndef CRAZY_RENDERER_HPP
#define CRAZY_RENDERER_HPP

#include <GLFW/glfw3.h>

namespace crazy {

/**
 * @brief Renderer class for OpenGL rendering operations
 * 
 * This class provides a simple abstraction for common OpenGL rendering
 * operations such as clearing the screen and setting clear colors.
 * 
 * Example usage:
 * @code
 * Renderer renderer;
 * renderer.setClearColor(0.1f, 0.1f, 0.2f, 1.0f);
 * 
 * while (!window.shouldClose()) {
 *     renderer.clear();
 *     // ... render content ...
 *     window.swapBuffers();
 * }
 * @endcode
 */
class Renderer {
public:
    /**
     * @brief Construct a new Renderer object
     */
    Renderer();
    
    /**
     * @brief Destroy the Renderer object
     */
    ~Renderer();
    
    /**
     * @brief Set the clear color
     * 
     * @param r Red component (0.0 to 1.0)
     * @param g Green component (0.0 to 1.0)
     * @param b Blue component (0.0 to 1.0)
     * @param a Alpha component (0.0 to 1.0)
     */
    void setClearColor(float r, float g, float b, float a);
    
    /**
     * @brief Clear the color buffer
     */
    void clear();
    
    /**
     * @brief Clear specified buffers
     * 
     * @param colorBuffer Clear color buffer if true
     * @param depthBuffer Clear depth buffer if true
     * @param stencilBuffer Clear stencil buffer if true
     */
    void clearBuffers(bool colorBuffer = true, bool depthBuffer = true, bool stencilBuffer = false);
    
    /**
     * @brief Enable or disable depth testing
     * 
     * @param enabled true to enable depth testing
     */
    void setDepthTest(bool enabled);
    
    /**
     * @brief Enable or disable blending
     * 
     * @param enabled true to enable blending
     */
    void setBlending(bool enabled);
    
    /**
     * @brief Get the OpenGL version string
     * 
     * @return const char* OpenGL version string or nullptr if unavailable
     */
    static const char* getOpenGLVersion();
    
    /**
     * @brief Get the OpenGL vendor string
     * 
     * @return const char* OpenGL vendor string or nullptr if unavailable
     */
    static const char* getOpenGLVendor();
    
    /**
     * @brief Get the OpenGL renderer string
     * 
     * @return const char* OpenGL renderer string or nullptr if unavailable
     */
    static const char* getOpenGLRenderer();

private:
    float m_clearColor[4];
};

} // namespace crazy

#endif // CRAZY_RENDERER_HPP
