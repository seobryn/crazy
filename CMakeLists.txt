# CMake configuration for the Crazy framework
cmake_minimum_required(VERSION 3.16)
project(crazy VERSION 0.1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# FetchContent for managing dependencies
include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)

# Configure GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Disable Wayland by default for broader CI/headless compatibility
# Users can re-enable with: cmake -DGLFW_BUILD_WAYLAND=ON
if(NOT DEFINED GLFW_BUILD_WAYLAND)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples/glfw)
