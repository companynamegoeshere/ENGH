#pragma once

#include <eobject/render/renderable_object.hpp>
#include <platform/render/index_buffer.hpp>

namespace ENGH::EObject::Render {

class Sphere : public RenderableObject {
  static Sphere *instance;
public:
  static inline Sphere &Get() {
    return *instance;
  }

  std::shared_ptr<Platform::Render::VertexArray> array;

  std::shared_ptr<Platform::Render::IndexBuffer> indexBuffer;

  void SetupRender(ENGH::Platform::Render::RenderContext &context) override;

  void ShutdownRender(ENGH::Platform::Render::RenderContext &context) override;
};

}
