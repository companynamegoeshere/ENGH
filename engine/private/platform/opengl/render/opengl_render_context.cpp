#include <platform/opengl/render/opengl_render_context.hpp>
#include <platform/opengl/render/opengl_index_render_buffer.hpp>

ENGH::Platform::Render::OpenGL::OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *window) : window(window) {}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::Setup() {
    glfwMakeContextCurrent(window);
    if(!gladLoadGL(glfwGetProcAddress)) {
        ENGH_CORE_FATAL("could not load opengl extensions");
    }
}

ENGH::Platform::Render::OpenGL::OpenGLRenderContext::~OpenGLRenderContext() {}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::SwapBuffers() {
    glfwSwapBuffers(window);
}

std::shared_ptr<ENGH::Platform::Render::IndexRenderBuffer> ENGH::Platform::Render::OpenGL::OpenGLRenderContext::CreateIndexBuffer() {
    return std::shared_ptr<IndexRenderBuffer>(); // TODO Real implementation
}

std::shared_ptr<ENGH::Platform::Render::VertexRenderBuffer> ENGH::Platform::Render::OpenGL::OpenGLRenderContext::CreateVertexBuffer() {
    return std::shared_ptr<VertexRenderBuffer>(); // TODO Real implementation
}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
