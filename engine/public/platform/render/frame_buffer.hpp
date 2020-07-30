#pragma once

#include <platform/render/render_device.hpp>

namespace ENGH::Platform::Render {

class FrameBuffer : public RenderDevice {
public:
  enum BufferType : ubyte {
    NONE    = 0u << 0u,
    COLOR   = 1u << 0u,
    DEPTH   = 1u << 1u,
    STENCIL = 1u << 1u
  };

  virtual void Invalidate() = 0;

  virtual void Resize(int64 width, int64 height) = 0;

  virtual uint32 GetWidth() = 0;

  virtual uint32 GetHeight() = 0;

  virtual uint GetColorTextureID() = 0;
};

}