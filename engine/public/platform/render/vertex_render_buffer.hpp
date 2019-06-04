#pragma once

#include <platform/render/render_buffer.hpp>

namespace ENGH::Platform::Render {

class VertexRenderBuffer : public RenderBuffer {
public:

    virtual void SetData(TArray<float> data) = 0;

};

}