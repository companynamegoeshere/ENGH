#include <eobject/component/box_component.hpp>

#include <array>

using namespace ENGH::Render;
using namespace ENGH::Render::Component;
using namespace ENGH::Math;

namespace ENGH::EObject::Comps {

static TArray<float> data;
static TArray<uint32> indexes;

Render::Component::PrimitiveRenderDelegate *BoxComponent::CreateRenderDelegate() {
  return nullptr;
}

}
