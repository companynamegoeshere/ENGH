#pragma once

#include <eobject/component/primitive_component.hpp>

namespace ENGH::Render::Component {
class PrimitiveStaticMeshRenderDelegate;
}

namespace ENGH::EObject::Comps {

class StaticMeshComponent : public PrimitiveComponent {
  friend class Render::Component::PrimitiveStaticMeshRenderDelegate;

public:
  explicit StaticMeshComponent();

  Render::Component::PrimitiveRenderDelegate *CreateRenderDelegate() override;
};

}
