#include <eobject/actor.hpp>
#include <eobject/component/primitive_component.hpp>
#include <eobject/world/world_registry.hpp>

#include <render/component/primitive_render_delegate.hpp>

using namespace ENGH::Render::Component;

namespace ENGH::EObject::Comps {

PrimitiveRenderDelegate *PrimitiveComponent::CreateRenderDelegate() {
  return nullptr;
}

void PrimitiveComponent::RegisterWorldFunctions() {
  Component::RegisterWorldFunctions();
  renderDelegate = this->CreateRenderDelegate();
  if(renderDelegate != nullptr) {
    owner->GetWorld()->GetRegistry().RegisterPrimitive(renderDelegate);
  }
}
PrimitiveComponent::~PrimitiveComponent() {
  if(renderDelegate != nullptr) {
    renderDelegate->primitive = nullptr;
  }
}

}
