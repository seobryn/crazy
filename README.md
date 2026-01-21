# crazy

Framework to build Desktop applications using React (frontend) with a C++17 core using GLFW/OpenGL.

## Features

- **C++ Wrappers for GLFW/OpenGL**: Object-oriented abstractions for window management, event handling, and rendering
- **Easy-to-use API**: High-level `Application` class for quick development
- **Flexible Architecture**: Use individual components or the complete application framework
- **Well-documented**: Comprehensive API documentation and examples

## C++ Wrappers

The framework provides four main wrapper classes:

- **`Window`**: GLFW window management with OpenGL context
- **`EventHandler`**: Callback-based event system for keyboard, mouse, and window events
- **`Renderer`**: OpenGL rendering abstractions
- **`Application`**: High-level application lifecycle coordinator

See [docs/wrappers/README.md](docs/wrappers/README.md) for detailed documentation.

## Quick Start

### Using the Application Class

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

## Build (C++ core)

Requirements:
- CMake >= 3.16
- A C++17-capable compiler (g++, clang, MSVC)

Build steps:

```bash
mkdir -p build
cd build
cmake -S .. -B .
cmake --build .
```

### Running Examples

After building, run the examples:

```bash
# GLFW example (raw GLFW/OpenGL)
./bin/glfw_demo

# Wrappers demo (using Application class)
./bin/wrappers_demo

# Simple wrappers test (using individual components)
./bin/simple_wrappers_test
```

## Extending the Wrappers

The wrappers are designed to be extended. Common extension points:

1. **Custom Events**: Add new event types to `EventHandler`
2. **Rendering Features**: Add drawing methods to `Renderer`
3. **Application Behavior**: Use callbacks in `Application` for custom logic

See [docs/wrappers/README.md](docs/wrappers/README.md) for detailed extension guide.

## Project Structure

```
crazy/
├── include/crazy/      # Public header files for wrappers
├── src/crazy/          # Implementation files for wrappers
├── examples/
│   ├── glfw/          # Raw GLFW/OpenGL example
│   └── wrappers/      # Examples using the wrappers
├── docs/wrappers/     # Detailed wrapper documentation
└── CMakeLists.txt     # Build configuration
```

## Documentation

- [Wrappers Documentation](docs/wrappers/README.md) - Complete guide to the C++ wrapper classes
- Examples in `examples/wrappers/` - Practical usage examples

## License

See LICENSE file for details.
