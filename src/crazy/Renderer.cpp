#include "crazy/Renderer.hpp"

namespace crazy {

Renderer::Renderer()
    : m_clearColor{0.0f, 0.0f, 0.0f, 1.0f}
{
}

Renderer::~Renderer() {
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    m_clearColor[0] = r;
    m_clearColor[1] = g;
    m_clearColor[2] = b;
    m_clearColor[3] = a;
    glClearColor(r, g, b, a);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer) {
    GLbitfield mask = 0;
    if (colorBuffer) mask |= GL_COLOR_BUFFER_BIT;
    if (depthBuffer) mask |= GL_DEPTH_BUFFER_BIT;
    if (stencilBuffer) mask |= GL_STENCIL_BUFFER_BIT;
    
    if (mask != 0) {
        glClear(mask);
    }
}

void Renderer::setDepthTest(bool enabled) {
    if (enabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::setBlending(bool enabled) {
    if (enabled) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}

void Renderer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

const char* Renderer::getOpenGLVersion() {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

const char* Renderer::getOpenGLVendor() {
    return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

const char* Renderer::getOpenGLRenderer() {
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

} // namespace crazy
