#pragma once

#include <platform/render/render_device.hpp>

namespace ENGH::Platform::Render {

class FrameBuffer : public RenderDevice {
public:
  enum class BufferType : ubyte {
    COLOR = 1 << 0,
    DEPTH = 1 << 1,
    /*STENCIL = 1 << 2 // TODO*/
  };

  virtual void Invalidate() = 0;

  virtual void Resize(uint32 width, uint32 height) = 0;
};

}