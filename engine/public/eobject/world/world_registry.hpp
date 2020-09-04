#pragma once

#include <core/engine.hpp>

namespace ENGH::Render {
class WorldRenderer;
}

namespace ENGH::Render::Component {
class PrimitiveRenderDelegate;
}

namespace ENGH::EObject::World {

class World;

class WorldRegistry {
  friend class World;
  friend class ENGH::Render::WorldRenderer;

  World *world;

  TArray<ENGH::Render::Component::PrimitiveRenderDelegate *> primitives;

  WorldRegistry(World *world);

public:
  void RegisterPrimitive(ENGH::Render::Component::PrimitiveRenderDelegate *primitiveRender);
};

}
