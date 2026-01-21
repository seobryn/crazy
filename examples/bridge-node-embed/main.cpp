#include <iostream>
#include <cstdlib>
#include <string>

#ifdef NODE_EMBED_ENABLED
#include <node.h>
#include <uv.h>

// Node.js embedding mode - in-process execution
int main(int argc, char* argv[]) {
    std::cout << "Running in Node.js EMBEDDED mode (in-process)" << std::endl;
    
    // Initialize Node.js
    // Note: This is a skeleton - real implementation would:
    // 1. Initialize libuv event loop
    // 2. Create Node.js platform and isolate
    // 3. Load and execute script.js in the embedded context
    // 4. Handle bidirectional C++ <-> JS communication
    
    std::cout << "TODO: Implement actual Node.js embedding using libnode API" << std::endl;
    std::cout << "This would allow direct C++ <-> JS function calls without subprocess overhead" << std::endl;
    
    return 0;
}

#else
// Subprocess fallback mode - spawn Node.js as external process
int main(int argc, char* argv[]) {
    std::cout << "Running in SUBPROCESS FALLBACK mode" << std::endl;
    std::cout << "To enable real embedding, rebuild with NODE_INCLUDE_DIR and NODE_LIBRARY" << std::endl;
    std::cout << std::endl;
    
    // Execute script.js using system Node.js installation
    std::string command = "node script.js";
    
    std::cout << "Executing: " << command << std::endl;
    std::cout << "--- Output from script.js ---" << std::endl;
    
    int result = system(command.c_str());
    
    std::cout << "--- End of script.js output ---" << std::endl;
    
    if (result == 0) {
        std::cout << "Script executed successfully" << std::endl;
        return 0;
    } else {
        std::cerr << "Script execution failed with code: " << result << std::endl;
        return 1;
    }
}
#endif
