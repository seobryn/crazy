# CMake Modules

This directory will contain custom CMake modules and helper scripts for the build system.

## Dependency Management

The project uses **CMake FetchContent** to manage external dependencies. This approach:
- Downloads and builds dependencies during the CMake configure step
- Ensures consistent versions across all platforms
- Eliminates the need for manual dependency installation (except system libraries like OpenGL)

### Current Dependencies

- **GLFW 3.4**: Window management and input handling (fetched via FetchContent)
- **OpenGL**: Graphics rendering (system library, requires platform-specific packages)

### Platform Requirements

**Linux**: Install OpenGL development packages
```bash
# Debian/Ubuntu
sudo apt-get install libgl1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

# Fedora/RHEL
sudo dnf install mesa-libGL-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
```

**macOS**: OpenGL framework included by default

**Windows**: OpenGL drivers included with graphics drivers

Future additions may include:
- Custom find modules for optional external libraries
- Build configuration helpers
