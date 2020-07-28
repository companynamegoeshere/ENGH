#pragma once

#include <eobject/render/renderable_object.hpp>
#include <platform/render/index_buffer.hpp>

namespace ENGH::EObject::Render {

class Sphere : public RenderableObject {
  uint32 latCount;
  uint32 longCount;
public:
  static std::shared_ptr<Sphere> Get(uint32 latCount, uint32 longCount);

  Sphere(uint32 latCount, uint32 longCount);

  std::shared_ptr<Platform::Render::VertexArray> array;

  std::shared_ptr<Platform::Render::IndexBuffer> indexBuffer;

  void SetupRender(ENGH::Platform::Render::RenderContext &context) override;

  void ShutdownRender(ENGH::Platform::Render::RenderContext &context) override;
};

}
