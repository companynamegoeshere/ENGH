#pragma once

#include <eobject/component/primitive_component.hpp>

namespace ENGH::EObject::Comps {

class SphereComponent : public PrimitiveComponent {
public:
  uint32 latCount = 40;
  uint32 longCount = 40;

  Render::Component::PrimitiveRenderDelegate *CreateRenderDelegate() override;
};

}
