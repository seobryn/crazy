# Node.js Embedding Prototype (C++ ↔ JS Bridge)

This directory contains a prototype for embedding Node.js into a C++ host application, enabling bidirectional communication between C++ and JavaScript code.

## Overview

The prototype supports two modes:

1. **Embedded Mode** (Real embedding) - Node.js runs in-process within the C++ application
2. **Subprocess Fallback Mode** - Node.js runs as an external process (default)

The fallback mode is used when libnode is not available, making it easy to test the prototype without complex build dependencies.

## Files

- `CMakeLists.txt` - CMake configuration with conditional compilation
- `main.cpp` - C++ host program with embedded/subprocess modes
- `script.js` - Example JavaScript file to be executed

## Quick Start (Subprocess Fallback Mode)

The easiest way to try the prototype is using the subprocess fallback mode, which only requires:
- CMake 3.15+
- C++17 compatible compiler
- Node.js installed on your system

### Build & Run

```bash
cd examples/bridge-node-embed
mkdir build && cd build
cmake ..
make
./bridge_node_embed
```

### Expected Output

```
Running in SUBPROCESS FALLBACK mode
To enable real embedding, rebuild with NODE_INCLUDE_DIR and NODE_LIBRARY

Executing: node script.js
--- Output from script.js ---
Hello from script.js!
Node.js version: v18.x.x
Platform: linux
Architecture: x64
...
--- End of script.js output ---
Script executed successfully
```

## Enabling Real Embedding Mode

To enable true in-process Node.js embedding, you need to build against libnode.

### Requirements

1. **libnode** - Node.js built as a shared library
2. **Node.js headers** - C++ API headers from Node.js source

### Building libnode

Node.js doesn't distribute pre-built libnode binaries, so you need to build it yourself:

```bash
# Clone Node.js source
git clone https://github.com/nodejs/node.git
cd node
git checkout v18.x  # or your preferred version

# Build Node.js as a shared library
./configure --shared
make -j$(nproc)

# After build completes:
# - libnode.so (or .dylib on macOS) will be in out/Release/
# - Headers will be in src/ and deps/
```

### Building the Prototype with Embedding

```bash
cd examples/bridge-node-embed
mkdir build && cd build

cmake .. \
  -DNODE_INCLUDE_DIR=/path/to/node/src \
  -DNODE_LIBRARY=/path/to/node/out/Release/libnode.so

make
./bridge_node_embed
```

**Note:** The current implementation is a skeleton. Real embedding requires:
- Initializing Node.js platform and V8 isolate
- Creating execution contexts
- Implementing C++ ↔ JS function call bridges
- Managing the libuv event loop

## Architecture

### Subprocess Mode (Current)
```
┌─────────────┐         ┌─────────────┐
│   C++ Host  │ spawn   │  node.exe   │
│  main.cpp   ├────────>│  script.js  │
└─────────────┘  stdio  └─────────────┘
```

### Embedded Mode (Goal)
```
┌───────────────────────────────────┐
│         C++ Process               │
│  ┌─────────────┐  ┌────────────┐ │
│  │  C++ Host   │<─>│  libnode   │ │
│  │  main.cpp   │  │  script.js │ │
│  └─────────────┘  └────────────┘ │
└───────────────────────────────────┘
```

## Limitations

This is a **prototype** with several limitations:

1. **Embedded mode is not implemented** - The `#ifdef NODE_EMBED_ENABLED` block is a skeleton
2. **No bidirectional communication** - C++ → JS and JS → C++ calls not implemented
3. **No error handling** - Minimal error handling in subprocess mode
4. **No async support** - No event loop integration
5. **No data serialization** - No mechanism to pass complex data structures

## Next Steps

To make this production-ready, consider:

1. **Implement Real Embedding**
   - Use libnode API to initialize V8 and Node.js runtime
   - Create execution context and load script.js
   - Implement proper cleanup and shutdown

2. **Add Bidirectional Bridges**
   - Expose C++ functions to JavaScript (using N-API or V8 API)
   - Allow JavaScript to call back into C++
   - Handle async operations across the boundary

3. **Alternative Approach: N-API Addon**
   - Instead of embedding Node.js in C++, create a Node.js addon
   - Use N-API (Node-API) for stable ABI across Node versions
   - Simpler build process and better Node.js ecosystem integration

4. **Add CI/CD**
   - Automated builds for both modes
   - Tests for subprocess and embedded modes
   - Multi-platform support (Linux, macOS, Windows)

5. **Improve Subprocess Mode**
   - Use pipes for stdin/stdout communication
   - Implement JSON-RPC or similar protocol
   - Add process lifecycle management

## References

- [Node.js Embedding Guide](https://nodejs.org/api/embedding.html)
- [N-API Documentation](https://nodejs.org/api/n-api.html)
- [V8 Embedder's Guide](https://v8.dev/docs/embed)

## License

Same as the main Crazy project.
