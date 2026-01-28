#include <crazy/Window.hpp>
#include <crazy/Renderer.hpp>
#include <crazy/EventHandler.hpp>
#include <iostream>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    std::cout << "=== Simple Wrapper Test ===" << std::endl;
    
    // Create a window
    crazy::Window window(640, 480, "Simple Wrapper Test");
    
    if (!window.isValid()) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    std::cout << "Window created: " << window.getWidth() << "x" << window.getHeight() << std::endl;
    
    // Make context current
    window.makeContextCurrent();
    window.setVSync(true);
    
    // Create renderer
    crazy::Renderer renderer;
    
    // Print OpenGL info
    std::cout << "OpenGL Version: " << crazy::Renderer::getOpenGLVersion() << std::endl;
    std::cout << "OpenGL Vendor: " << crazy::Renderer::getOpenGLVendor() << std::endl;
    std::cout << "OpenGL Renderer: " << crazy::Renderer::getOpenGLRenderer() << std::endl;
    
    // Create event handler
    crazy::EventHandler eventHandler;
    eventHandler.attachToWindow(window);
    
    // Set up event callbacks
    eventHandler.setKeyPressCallback([&window](const crazy::KeyEvent& event) {
        if (event.key == GLFW_KEY_ESCAPE) {
            std::cout << "ESC pressed, closing..." << std::endl;
            window.setShouldClose(true);
        }
    });
    
    std::cout << "Press ESC to close the window" << std::endl;
    
    // Set clear color
    renderer.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // Main loop
    int frameCount = 0;
    while (!window.shouldClose()) {
        // Clear
        renderer.clear();
        
        // Swap buffers
        window.swapBuffers();
        
        // Poll events
        crazy::EventHandler::pollEvents();
        
        frameCount++;
    }
    
    std::cout << "Rendered " << frameCount << " frames" << std::endl;
    
    // Cleanup
    glfwTerminate();
    
    std::cout << "Test completed successfully!" << std::endl;
    return 0;
}
