#pragma once

#include <platform/render/render_buffer.hpp>

namespace ENGH::Platform::Render {

class VertexRenderBuffer : public RenderBuffer {
public:

    virtual void SetData(const TArray<float> &data) = 0;

};

}