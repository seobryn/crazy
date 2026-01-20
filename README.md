# crazy

Framework to build Desktop applications using React (frontend) with a C++17 core using GLFW/OpenGL.

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
./crazy_app
```

This minimal setup builds a "Hello Crazy" test program. Next steps include adding GLFW/OpenGL and the frontend integration.
