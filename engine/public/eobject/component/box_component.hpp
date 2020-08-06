#pragma once

#include <eobject/component/primitive_component.hpp>

namespace ENGH::EObject::Comps {

class BoxComponent : public PrimitiveComponent {
public:
  Render::Component::PrimitiveRenderDelegate *CreateRenderDelegate() override;
};

}
