#include "crazy/Application.hpp"
#include <iostream>

namespace crazy {

Application::Application(int width, int height, const std::string& title)
    : m_initialized(false)
    , m_window(nullptr)
    , m_eventHandler(nullptr)
    , m_renderer(nullptr)
    , m_initCallback(nullptr)
    , m_updateCallback(nullptr)
    , m_renderCallback(nullptr)
    , m_shutdownCallback(nullptr)
    , m_lastFrameTime(0.0)
{
    // Set error callback for GLFW
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    });
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    
    // Create window
    m_window = std::make_unique<Window>(width, height, title);
    if (!m_window->isValid()) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }
    
    // Make context current
    m_window->makeContextCurrent();
    
    // Create event handler and renderer
    m_eventHandler = std::make_unique<EventHandler>();
    m_renderer = std::make_unique<Renderer>();
    
    // Attach event handler to window
    m_eventHandler->attachToWindow(*m_window);
    
    // Enable VSync by default
    m_window->setVSync(true);
    
    m_initialized = true;
}

Application::~Application() {
    shutdown();
}

bool Application::initialize() {
    if (!m_initialized) {
        std::cerr << "Application initialization failed" << std::endl;
        return false;
    }
    
    // Call user initialization callback
    if (m_initCallback) {
        m_initCallback();
    }
    
    return true;
}

int Application::run() {
    if (!m_initialized) {
        std::cerr << "Cannot run uninitialized application" << std::endl;
        return -1;
    }
    
    // Call initialization
    if (!initialize()) {
        return -1;
    }
    
    std::cout << "Application started successfully" << std::endl;
    std::cout << "OpenGL Version: " << Renderer::getOpenGLVersion() << std::endl;
    
    // Initialize timing
    m_lastFrameTime = glfwGetTime();
    
    // Main loop
    while (!m_window->shouldClose()) {
        // Calculate delta time
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - m_lastFrameTime);
        m_lastFrameTime = currentTime;
        
        // Update
        if (m_updateCallback) {
            m_updateCallback(deltaTime);
        }
        
        // Render
        if (m_renderCallback) {
            m_renderCallback();
        }
        
        // Swap buffers
        m_window->swapBuffers();
        
        // Poll events
        EventHandler::pollEvents();
    }
    
    std::cout << "Application shutting down" << std::endl;
    
    return 0;
}

void Application::shutdown() {
    if (!m_initialized) {
        return;
    }
    
    // Call user shutdown callback
    if (m_shutdownCallback) {
        m_shutdownCallback();
    }
    
    // Clean up
    m_renderer.reset();
    m_eventHandler.reset();
    m_window.reset();
    
    // Terminate GLFW
    glfwTerminate();
    
    m_initialized = false;
}

void Application::setInitCallback(InitCallback callback) {
    m_initCallback = callback;
}

void Application::setUpdateCallback(UpdateCallback callback) {
    m_updateCallback = callback;
}

void Application::setRenderCallback(RenderCallback callback) {
    m_renderCallback = callback;
}

void Application::setShutdownCallback(ShutdownCallback callback) {
    m_shutdownCallback = callback;
}

Window& Application::getWindow() {
    return *m_window;
}

EventHandler& Application::getEventHandler() {
    return *m_eventHandler;
}

Renderer& Application::getRenderer() {
    return *m_renderer;
}

void Application::quit() {
    if (m_window) {
        m_window->setShouldClose(true);
    }
}

} // namespace crazy
