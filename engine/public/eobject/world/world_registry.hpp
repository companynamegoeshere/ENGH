#pragma once

#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::EObject::World {

class WorldRegistry {
  TArray<ENGH::Render::Component::PrimitiveRenderDelegate*> render;
public:
  void RegisterPrimitive(ENGH::Render::Component::PrimitiveRenderDelegate* primitiveRender);
};

}
