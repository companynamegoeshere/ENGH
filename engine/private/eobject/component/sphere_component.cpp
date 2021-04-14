#include <eobject/component/sphere_component.hpp>

using namespace ENGH::Render;
using namespace ENGH::Render::Component;

namespace ENGH::EObject::Comps {

Render::Component::PrimitiveRenderDelegate *SphereComponent::CreateRenderDelegate() {
  return nullptr;
}

}
