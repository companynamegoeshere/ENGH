#pragma once

#include <platform/render/buffer_layout.hpp>
#include <platform/render/render_buffer.hpp>

namespace ENGH::Platform::Render {

class VertexBuffer : public RenderBuffer {
public:

    virtual void SetData(const TArray<float> &data) = 0;

    virtual void SetLayout(const BufferLayout& layout) = 0;

    virtual const BufferLayout& GetLayout() = 0;

};

}