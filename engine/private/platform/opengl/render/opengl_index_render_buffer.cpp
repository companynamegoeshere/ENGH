#include <platform/opengl/render/opengl_index_render_buffer.hpp>

ENGH::Platform::Render::OpenGL::OpenGLIndexRenderBuffer::OpenGLIndexRenderBuffer() {
    glCreateBuffers(1, &id);
}

void ENGH::Platform::Render::OpenGL::OpenGLIndexRenderBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ENGH::Platform::Render::OpenGL::OpenGLIndexRenderBuffer::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ENGH::Platform::Render::OpenGL::OpenGLIndexRenderBuffer::~OpenGLIndexRenderBuffer() {
    glDeleteBuffers(1, &id);
}
