#include <eobject/component/primitive_component.hpp>
#include <eobject/world/world_registry.hpp>

using namespace ENGH::Render::Component;

namespace ENGH::EObject::Comps {

PrimitiveRenderDelegate *PrimitiveComponent::CreateRenderDelegate() {
  return nullptr;
}
void PrimitiveComponent::RegisterWorldFunctions(World::WorldRegistry &registry) {
  Component::RegisterWorldFunctions(registry);
  registry.RegisterPrimitive(CreateRenderDelegate());
}

}
