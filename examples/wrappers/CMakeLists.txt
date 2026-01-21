# Wrappers example executable
add_executable(wrappers_demo main.cpp)

# Link libraries
target_link_libraries(wrappers_demo PRIVATE crazy_wrappers)

# Set output directory
set_target_properties(wrappers_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Simple test executable
add_executable(simple_wrappers_test simple_test.cpp)

# Link libraries
target_link_libraries(simple_wrappers_test PRIVATE crazy_wrappers)

# Set output directory
set_target_properties(simple_wrappers_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
