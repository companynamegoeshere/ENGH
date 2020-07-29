#include <platform/opengl/render/frame_buffer.hpp>

namespace ENGH::Platform::Render::OpenGL {

static constexpr GLuint emptyID = ~static_cast<GLuint>(0);

OpenGLFrameBuffer::OpenGLFrameBuffer(BufferType type) : type(type), fbo(emptyID) {

}

OpenGLFrameBuffer::~OpenGLFrameBuffer() {
  deleteData();
}

void OpenGLFrameBuffer::Invalidate() {
  deleteData();

  glCreateFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void OpenGLFrameBuffer::deleteData() {
  if (fbo == 0 || fbo == emptyID) {
    return;
  }
  glDeleteFramebuffers(1, &fbo);
}

void OpenGLFrameBuffer::Resize(ENGH::uint32 width, ENGH::uint32 height) {

}

void OpenGLFrameBuffer::Bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}
void OpenGLFrameBuffer::Unbind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

};
