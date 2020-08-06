#include <eobject/component/sphere_component.hpp>
#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::EObject::Comps {

Render::Component::PrimitiveRenderDelegate *SphereComponent::CreateRenderDelegate() {
  return PrimitiveComponent::CreateRenderDelegate();
}

}
