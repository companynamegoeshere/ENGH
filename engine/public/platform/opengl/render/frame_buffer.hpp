#pragma once

#include <platform/opengl/render/render_context.hpp>
#include <platform/render/frame_buffer.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLFrameBuffer : public FrameBuffer {
  BufferType type;
  GLuint fbo;

  inline void deleteData();
public:
  OpenGLFrameBuffer(BufferType type);

  ~OpenGLFrameBuffer();

  void Invalidate() override;

  void Resize(uint32 width, uint32 height) override;

  void Bind() const override;

  void Unbind() const override;
};

}
