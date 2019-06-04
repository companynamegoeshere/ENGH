#include <platform/opengl/render/opengl_vertex_render_buffer.hpp>

ENGH::Platform::Render::OpenGL::OpenGLVertexRenderBuffer::OpenGLVertexRenderBuffer() {
    glCreateBuffers(1, &id);
}

ENGH::Platform::Render::OpenGL::OpenGLVertexRenderBuffer::~OpenGLVertexRenderBuffer() {
    glDeleteBuffers(1, &id);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexRenderBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexRenderBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexRenderBuffer::SetData(const TArray<float> &data) {
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, data.length() * sizeof(float), data.data(), GL_STATIC_DRAW);
}
