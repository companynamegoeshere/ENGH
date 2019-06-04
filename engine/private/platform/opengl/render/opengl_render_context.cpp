#include <platform/opengl/render/opengl_render_context.hpp>
#include <platform/opengl/render/opengl_index_render_buffer.hpp>

ENGH::Platform::Render::OpenGL::OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *window) : window(window) {}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::Setup() {

}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::SwapBuffers() {

}

std::shared_ptr<ENGH::Platform::Render::IndexRenderBuffer> ENGH::Platform::Render::OpenGL::OpenGLRenderContext::CreateIndexBuffer() {
    return std::shared_ptr<IndexRenderBuffer>(); // TODO Real implementation
}

std::shared_ptr<ENGH::Platform::Render::VertexRenderBuffer> ENGH::Platform::Render::OpenGL::OpenGLRenderContext::CreateVertexBuffer() {
    return std::shared_ptr<VertexRenderBuffer>(); // TODO Real implementation
}

ENGH::Platform::Render::OpenGL::OpenGLRenderContext::~OpenGLRenderContext() {

}
