#include <eobject/component/box_component.hpp>
#include <render/component/primitive_box_render_delegate.hpp>

namespace ENGH::EObject::Comps {

Render::Component::PrimitiveRenderDelegate *BoxComponent::CreateRenderDelegate() {
  return new Render::Component::PrimitiveBoxRenderDelegate(this);
}

}
