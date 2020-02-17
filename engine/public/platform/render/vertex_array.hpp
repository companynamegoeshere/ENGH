#pragma once

#include "render_device.hpp"
#include "vertex_buffer.hpp"

namespace ENGH::Platform::Render {

class VertexArray : public RenderDevice {
public:

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

    virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;

};

}
