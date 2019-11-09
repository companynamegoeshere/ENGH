#include <platform/opengl/render/index_buffer.hpp>

ENGH::Platform::Render::OpenGL::OpenGLIndexBuffer::OpenGLIndexBuffer() {
    this->count = 0;
    glGenBuffers(1, &ibo);
}

ENGH::Platform::Render::OpenGL::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1, &ibo);
}

void ENGH::Platform::Render::OpenGL::OpenGLIndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void ENGH::Platform::Render::OpenGL::OpenGLIndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ENGH::Platform::Render::OpenGL::OpenGLIndexBuffer::SetData(const TArray<uint32>& data) {
  this->count = data.length();
  this->Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * UInt32::SIZE, data.data(), GL_STATIC_DRAW);
}
