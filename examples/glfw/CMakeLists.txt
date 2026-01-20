# GLFW example executable
add_executable(glfw_demo main.cpp)

# Link libraries
target_link_libraries(glfw_demo PRIVATE glfw OpenGL::GL)

# Set output directory
set_target_properties(glfw_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
