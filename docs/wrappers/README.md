# Crazy Framework - C++ Wrappers Documentation

## Overview

The Crazy framework provides a set of C++ wrappers for GLFW/OpenGL that simplify window management, event handling, and rendering. These wrappers are designed to be easy to use while providing flexibility for extending functionality.

## Architecture

The wrapper system consists of four main components:

### 1. Window (`crazy::Window`)

The `Window` class wraps GLFW window functionality, providing a clean C++ interface for:
- Window creation and destruction
- Window properties (size, title)
- OpenGL context management
- VSync control

**Key Features:**
- RAII-compliant (Resource Acquisition Is Initialization)
- Move semantics support
- No copy construction (windows are unique resources)

### 2. EventHandler (`crazy::EventHandler`)

The `EventHandler` class provides a callback-based event system for:
- Keyboard events (press, release, repeat)
- Mouse events (button press/release, movement)
- Window events (resize, close)

**Key Features:**
- Type-safe event callbacks using `std::function`
- Separate callbacks for different event types
- Easy attachment to windows

### 3. Renderer (`crazy::Renderer`)

The `Renderer` class provides basic OpenGL rendering abstractions:
- Clear color management
- Buffer clearing (color, depth, stencil)
- Depth testing and blending control
- OpenGL version information

**Key Features:**
- Simple API for common rendering tasks
- Static methods for querying OpenGL capabilities
- Future-ready for more advanced rendering features

### 4. Application (`crazy::Application`)

The `Application` class coordinates all components and manages the application lifecycle:
- Initialization and shutdown
- Main render loop
- Delta time calculation
- Integration of Window, EventHandler, and Renderer

**Key Features:**
- High-level abstraction for application structure
- Callback-based architecture for user code
- Automatic timing and frame management

## Usage Examples

### Basic Application

```cpp
#include <crazy/Application.hpp>

int main() {
    crazy::Application app(800, 600, "My App");
    
    app.setRenderCallback([&app]() {
        app.getRenderer().setClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        app.getRenderer().clear();
    });
    
    app.getEventHandler().setKeyPressCallback([&app](const crazy::KeyEvent& event) {
        if (event.key == GLFW_KEY_ESCAPE) {
            app.quit();
        }
    });
    
    return app.run();
}
```

### Manual Component Usage

```cpp
#include <crazy/Window.hpp>
#include <crazy/Renderer.hpp>
#include <crazy/EventHandler.hpp>

int main() {
    glfwInit();
    
    crazy::Window window(800, 600, "My App");
    window.makeContextCurrent();
    window.setVSync(true);
    
    crazy::Renderer renderer;
    renderer.setClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    
    crazy::EventHandler handler;
    handler.attachToWindow(window);
    handler.setKeyPressCallback([&window](const crazy::KeyEvent& event) {
        if (event.key == GLFW_KEY_ESCAPE) {
            window.setShouldClose(true);
        }
    });
    
    while (!window.shouldClose()) {
        renderer.clear();
        window.swapBuffers();
        crazy::EventHandler::pollEvents();
    }
    
    glfwTerminate();
    return 0;
}
```

## Extending the Wrappers

### Adding Custom Event Types

To add custom event handling:

1. Define your event structure in `EventHandler.hpp`:
```cpp
struct CustomEvent {
    int customData;
};
```

2. Add callback typedef:
```cpp
using CustomCallback = std::function<void(const CustomEvent&)>;
```

3. Add callback setter and member:
```cpp
void setCustomCallback(CustomCallback callback);
private:
    CustomCallback m_customCallback;
```

4. Implement the callback logic in `EventHandler.cpp`

### Extending the Renderer

To add rendering features:

1. Add new methods to `Renderer.hpp`:
```cpp
void drawTriangle(float x, float y, float size);
```

2. Implement in `Renderer.cpp`:
```cpp
void Renderer::drawTriangle(float x, float y, float size) {
    // OpenGL drawing code
}
```

### Custom Application Behavior

The `Application` class can be extended through callbacks:

- `setInitCallback()` - Called once after initialization
- `setUpdateCallback()` - Called every frame before rendering
- `setRenderCallback()` - Called every frame for rendering
- `setShutdownCallback()` - Called during shutdown

## Building with the Wrappers

To use the wrappers in your CMake project:

```cmake
# In your CMakeLists.txt
target_link_libraries(your_target PRIVATE crazy_wrappers)
```

The wrappers library automatically links GLFW and OpenGL.

## API Reference

### Window Class

```cpp
Window(int width, int height, const std::string& title);
bool isValid() const;
bool shouldClose() const;
void setShouldClose(bool value);
void makeContextCurrent();
void swapBuffers();
int getWidth() const;
int getHeight() const;
void setTitle(const std::string& title);
void setVSync(bool enabled);
GLFWwindow* getNativeWindow() const;
```

### EventHandler Class

```cpp
void attachToWindow(Window& window);
void setKeyPressCallback(KeyCallback callback);
void setKeyReleaseCallback(KeyCallback callback);
void setKeyRepeatCallback(KeyCallback callback);
void setMouseButtonPressCallback(MouseButtonCallback callback);
void setMouseButtonReleaseCallback(MouseButtonCallback callback);
void setMouseMoveCallback(MouseMoveCallback callback);
void setWindowResizeCallback(WindowResizeCallback callback);
void setWindowCloseCallback(WindowCloseCallback callback);
static void pollEvents();
```

### Renderer Class

```cpp
void setClearColor(float r, float g, float b, float a);
void clear();
void clearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer);
void setDepthTest(bool enabled);
void setBlending(bool enabled);
static const char* getOpenGLVersion();
static const char* getOpenGLVendor();
static const char* getOpenGLRenderer();
```

### Application Class

```cpp
Application(int width, int height, const std::string& title);
bool initialize();
int run();
void shutdown();
void setInitCallback(InitCallback callback);
void setUpdateCallback(UpdateCallback callback);
void setRenderCallback(RenderCallback callback);
void setShutdownCallback(ShutdownCallback callback);
Window& getWindow();
EventHandler& getEventHandler();
Renderer& getRenderer();
void quit();
```

## Thread Safety

The wrappers are **not thread-safe** by default. All operations should be performed on the main thread, as required by GLFW and OpenGL.

## Performance Considerations

- VSync is enabled by default for smooth rendering
- Event polling is done once per frame
- Delta time is calculated automatically by `Application`
- The `MouseMoveCallback` can be called very frequently; avoid heavy processing in this callback

## Future Enhancements

Potential areas for extension:
- Shader management
- Texture loading
- 3D camera systems
- Input state queries (is key currently pressed?)
- Multi-window support
- Gamepad/joystick support
