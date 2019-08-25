#include <platform/opengl/render/render_context.hpp>
#include <platform/opengl/render/index_buffer.hpp>
#include <platform/opengl/render/vertex_buffer.hpp>

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

std::shared_ptr<ENGH::Platform::Render::IndexBuffer> ENGH::Platform::Render::OpenGL::OpenGLRenderContext::CreateIndexBuffer() {
    return std::make_shared<OpenGLIndexBuffer>();
}

std::shared_ptr<ENGH::Platform::Render::VertexBuffer> ENGH::Platform::Render::OpenGL::OpenGLRenderContext::CreateVertexBuffer() {
    return std::make_shared<OpenGLVertexBuffer>();
}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
