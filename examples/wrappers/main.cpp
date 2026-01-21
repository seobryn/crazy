#include <crazy/Application.hpp>
#include <iostream>

int main() {
    // Create application with 800x600 window
    crazy::Application app(800, 600, "Crazy Wrappers Demo");
    
    // Set up initialization callback
    app.setInitCallback([]() {
        std::cout << "Application initialized!" << std::endl;
    });
    
    // Set up update callback
    app.setUpdateCallback([](float deltaTime) {
        // Update logic here (called every frame)
        // deltaTime is in seconds
    });
    
    // Set up render callback
    app.setRenderCallback([&app]() {
        // Set clear color (dark blue)
        app.getRenderer().setClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        app.getRenderer().clear();
        
        // Render your content here
    });
    
    // Set up event handlers
    app.getEventHandler().setKeyPressCallback([&app](const crazy::KeyEvent& event) {
        if (event.key == GLFW_KEY_ESCAPE) {
            std::cout << "ESC pressed, closing window..." << std::endl;
            app.quit();
        }
        
        if (event.key == GLFW_KEY_SPACE) {
            std::cout << "SPACE pressed!" << std::endl;
        }
    });
    
    app.getEventHandler().setMouseButtonPressCallback([](const crazy::MouseButtonEvent& event) {
        std::cout << "Mouse button " << event.button << " pressed" << std::endl;
    });
    
    app.getEventHandler().setMouseMoveCallback([](const crazy::MouseMoveEvent& event) {
        // This can be very verbose, so we don't print it
        // std::cout << "Mouse moved to: " << event.xpos << ", " << event.ypos << std::endl;
    });
    
    app.getEventHandler().setWindowResizeCallback([](const crazy::WindowResizeEvent& event) {
        std::cout << "Window resized to: " << event.width << "x" << event.height << std::endl;
        glViewport(0, 0, event.width, event.height);
    });
    
    // Set up shutdown callback
    app.setShutdownCallback([]() {
        std::cout << "Application shutting down!" << std::endl;
    });
    
    std::cout << "Press ESC to exit" << std::endl;
    std::cout << "Press SPACE to test key events" << std::endl;
    std::cout << "Click mouse buttons to test mouse events" << std::endl;
    
    // Run the application
    return app.run();
}
