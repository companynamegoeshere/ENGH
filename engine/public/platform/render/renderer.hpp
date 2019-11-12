#pragma once

#include <platform/render/vertex_array.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::Platform::Render {

class Renderer {
public:

  virtual void Clear(float r, float g, float b, float a) = 0;

  virtual void DrawVertexArray(const std::shared_ptr<VertexArray> &array) = 0;

  virtual ~Renderer() = 0;
};

}
