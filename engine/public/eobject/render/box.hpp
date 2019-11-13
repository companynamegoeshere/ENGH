#pragma once

#include <eobject/render/renderable_object.hpp>

namespace ENGH::EObject::Render {

class Box : public RenderableObject {
public:
  static Box *INSTANCE;

  std::shared_ptr<Platform::Render::VertexArray> array;

  void SetupRender(ENGH::Platform::Render::RenderContext &context) override;

  void ShutdownRender(ENGH::Platform::Render::RenderContext &context) override;
};

}
