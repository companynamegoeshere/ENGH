#include <eobject/component/box_component.hpp>
#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::EObject::Comps {

Render::Component::PrimitiveRenderDelegate *BoxComponent::CreateRenderDelegate() {
  return PrimitiveComponent::CreateRenderDelegate();
}

}
