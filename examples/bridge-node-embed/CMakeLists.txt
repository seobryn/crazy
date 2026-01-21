cmake_minimum_required(VERSION 3.15)
project(bridge_node_embed)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if NODE_INCLUDE_DIR and NODE_LIBRARY are provided
if(DEFINED NODE_INCLUDE_DIR AND DEFINED NODE_LIBRARY)
    message(STATUS "Node.js embedding enabled")
    message(STATUS "NODE_INCLUDE_DIR: ${NODE_INCLUDE_DIR}")
    message(STATUS "NODE_LIBRARY: ${NODE_LIBRARY}")
    
    add_compile_definitions(NODE_EMBED_ENABLED)
    
    add_executable(bridge_node_embed main.cpp)
    
    target_include_directories(bridge_node_embed PRIVATE ${NODE_INCLUDE_DIR})
    target_link_libraries(bridge_node_embed PRIVATE ${NODE_LIBRARY})
else()
    message(STATUS "Node.js embedding disabled - using subprocess fallback mode")
    message(STATUS "To enable embedding, provide NODE_INCLUDE_DIR and NODE_LIBRARY")
    
    add_executable(bridge_node_embed main.cpp)
endif()

# Copy script.js to build directory
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/script.js
    ${CMAKE_CURRENT_BINARY_DIR}/script.js
    COPYONLY
)
