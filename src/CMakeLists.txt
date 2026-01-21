# Crazy framework wrappers library
add_library(crazy_wrappers
    crazy/Window.cpp
    crazy/EventHandler.cpp
    crazy/Renderer.cpp
    crazy/Application.cpp
)

# Link libraries
target_link_libraries(crazy_wrappers PUBLIC glfw OpenGL::GL)

# Set include directories
target_include_directories(crazy_wrappers PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# Source files for the main executable
add_executable(crazy_app main.cpp)

# Link against libraries
target_link_libraries(crazy_app PRIVATE crazy_wrappers)
