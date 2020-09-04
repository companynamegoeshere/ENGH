#include <eobject/world/world_registry.hpp>

using ENGH::Render::Component::PrimitiveRenderDelegate;

namespace ENGH::EObject::World {

WorldRegistry::WorldRegistry(World *world) : world(world) {
}

void WorldRegistry::RegisterPrimitive(PrimitiveRenderDelegate *primitiveRender) {
  this->primitives += primitiveRender;
}

}