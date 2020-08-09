#include <eobject/world/world_registry.hpp>

#include <render/component/primitive_render_delegate.hpp>

using ENGH::Render::Component::PrimitiveRenderDelegate;

namespace ENGH::EObject::World {

void WorldRegistry::RegisterPrimitive(PrimitiveRenderDelegate *primitiveRender) {
  this->render += primitiveRender;
}

}