#include <platform/opengl/render/frame_buffer.hpp>

namespace ENGH::Platform::Render::OpenGL {

// FBO == 0 means it's the screen

OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBuffer::BufferType type, uint32 width, uint32 height, GLuint fbo) :
    type(type),
    width(width),
    height(height),
    fbo(fbo) {}

OpenGLFrameBuffer::~OpenGLFrameBuffer() {
  deleteData();
}

void OpenGLFrameBuffer::Invalidate() {
  if (fbo == 0) {
    return;
  }
  deleteData();

  glCreateFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  bool color   = 0 != (type & BufferType::COLOR);
  bool depth   = 0 != (type & BufferType::DEPTH);
  bool stencil = 0 != (type & BufferType::STENCIL);

  auto attachTexture = [this](GLuint *target, GLenum attachment, GLint internalFormat, GLint format, GLenum texType) {
    glGenTextures(1, target);

    glBindTexture(GL_TEXTURE_2D, *target);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, texType, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, *target, 0);
  };

  if (color) {
    attachTexture(&textures[0], GL_COLOR_ATTACHMENT0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
  }
  if (depth && stencil) {
    attachTexture(&textures[1], GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);
  } else if (depth) {
    attachTexture(&textures[1], GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT);
  } else if (stencil) {
    attachTexture(&textures[1], GL_STENCIL_ATTACHMENT, GL_STENCIL_INDEX, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE);
  }

#ifdef ENGH_DEBUG
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    ENGH_CORE_ERROR("Could not create framebuffer!");
  }
#endif
}

void OpenGLFrameBuffer::deleteData() {
  if (fbo == 0 || fbo == emptyID) {
    return;
  }
  glDeleteFramebuffers(1, &fbo);
  glDeleteTextures(2, textures);
  fbo = emptyID;
  textures[0] = 0;
  textures[1] = 0;
}

void OpenGLFrameBuffer::Resize(uint32 width, uint32 height) {
  this->width  = width;
  this->height = height;
  Invalidate();
}

uint32 OpenGLFrameBuffer::GetWidth() {
  return width;
}

uint32 OpenGLFrameBuffer::GetHeight() {
  return height;
}

void OpenGLFrameBuffer::Bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glViewport(0, 0, width, height);
}
void OpenGLFrameBuffer::Unbind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint OpenGLFrameBuffer::GetColorTextureID() {
  return static_cast<uint>(textures[0]);
}

GLuint OpenGLFrameBuffer::GetSecondTextureID() {
  return textures[1];
}

};
