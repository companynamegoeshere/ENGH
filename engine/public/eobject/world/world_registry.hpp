#pragma once

#include <core/engine.hpp>

namespace ENGH::Render::Component {
class PrimitiveRenderDelegate;
}

namespace ENGH::EObject::World {

class World;

class WorldRegistry {
  friend class World;

  World *world;

  TArray<ENGH::Render::Component::PrimitiveRenderDelegate *> render;

  WorldRegistry(World *world);

public:
  void RegisterPrimitive(ENGH::Render::Component::PrimitiveRenderDelegate *primitiveRender);
};

}
