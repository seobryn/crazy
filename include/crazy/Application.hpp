#ifndef CRAZY_APPLICATION_HPP
#define CRAZY_APPLICATION_HPP

#include "Window.hpp"
#include "EventHandler.hpp"
#include "Renderer.hpp"
#include <functional>
#include <memory>

namespace crazy {

/**
 * @brief Application class for coordinating the main render loop
 * 
 * This class provides a high-level abstraction for managing the application
 * lifecycle, including initialization, the main render loop, and cleanup.
 * 
 * Example usage:
 * @code
 * crazy::Application app(800, 600, "My App");
 * 
 * app.setUpdateCallback([](float deltaTime) {
 *     // Update game logic
 * });
 * 
 * app.setRenderCallback([]() {
 *     // Render content
 * });
 * 
 * return app.run();
 * @endcode
 */
class Application {
public:
    using UpdateCallback = std::function<void(float deltaTime)>;
    using RenderCallback = std::function<void()>;
    using InitCallback = std::function<void()>;
    using ShutdownCallback = std::function<void()>;
    
    /**
     * @brief Construct a new Application object
     * 
     * @param width Window width in pixels
     * @param height Window height in pixels
     * @param title Window title
     */
    Application(int width, int height, const std::string& title);
    
    /**
     * @brief Destroy the Application object
     */
    ~Application();
    
    /**
     * @brief Initialize GLFW and the application
     * 
     * @return true if initialization succeeded
     * @return false if initialization failed
     */
    bool initialize();
    
    /**
     * @brief Run the main application loop
     * 
     * @return int Exit code (0 for success)
     */
    int run();
    
    /**
     * @brief Shutdown the application
     */
    void shutdown();
    
    /**
     * @brief Set the initialization callback
     * 
     * Called once after successful initialization, before the main loop starts.
     * 
     * @param callback Initialization callback function
     */
    void setInitCallback(InitCallback callback);
    
    /**
     * @brief Set the update callback
     * 
     * Called once per frame before rendering. Receives delta time in seconds.
     * 
     * @param callback Update callback function
     */
    void setUpdateCallback(UpdateCallback callback);
    
    /**
     * @brief Set the render callback
     * 
     * Called once per frame for rendering operations.
     * 
     * @param callback Render callback function
     */
    void setRenderCallback(RenderCallback callback);
    
    /**
     * @brief Set the shutdown callback
     * 
     * Called once during shutdown, before cleanup.
     * 
     * @param callback Shutdown callback function
     */
    void setShutdownCallback(ShutdownCallback callback);
    
    /**
     * @brief Get the window object
     * 
     * @return Window& Reference to the window
     */
    Window& getWindow();
    
    /**
     * @brief Get the event handler
     * 
     * @return EventHandler& Reference to the event handler
     */
    EventHandler& getEventHandler();
    
    /**
     * @brief Get the renderer
     * 
     * @return Renderer& Reference to the renderer
     */
    Renderer& getRenderer();
    
    /**
     * @brief Request application exit
     */
    void quit();

private:
    bool m_initialized;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<EventHandler> m_eventHandler;
    std::unique_ptr<Renderer> m_renderer;
    
    InitCallback m_initCallback;
    UpdateCallback m_updateCallback;
    RenderCallback m_renderCallback;
    ShutdownCallback m_shutdownCallback;
    
    double m_lastFrameTime;
};

} // namespace crazy

#endif // CRAZY_APPLICATION_HPP
