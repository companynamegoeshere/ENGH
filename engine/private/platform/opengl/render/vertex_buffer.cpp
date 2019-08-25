#include <platform/opengl/render/vertex_buffer.hpp>

ENGH::Platform::Render::OpenGL::OpenGLVertexBuffer::OpenGLVertexBuffer() {
    glCreateBuffers(1, &vbo);
}

ENGH::Platform::Render::OpenGL::OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &vbo);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexBuffer::SetData(const TArray<float> &data) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, data.length() * data.dataType.SIZE, data.data(), GL_STATIC_DRAW);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexBuffer::SetLayout(const BufferLayoutEntry &layout) {
    this->layout = layout;
}
