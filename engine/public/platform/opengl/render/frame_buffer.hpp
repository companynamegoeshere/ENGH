#pragma once

#include <platform/render/frame_buffer.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLFrameBuffer : public FrameBuffer {
  BufferType type;
  uint32     width, height;
  GLuint     fbo;
  GLuint     textures[2] = {0};

  inline void deleteData();

  static constexpr GLuint emptyID = ~static_cast<GLuint>(0);
public:
  OpenGLFrameBuffer(BufferType type, int64 width, int64 height, GLuint fbo = emptyID);

  ~OpenGLFrameBuffer() override;

  void Invalidate() override;

  void Resize(int64 width, int64 height) override;

  uint32 GetWidth() override;

  uint32 GetHeight() override;

  void Bind() const override;

  void Unbind() const override;

  uint GetColorTextureID() override;

  virtual GLuint GetSecondTextureID();
};

}
