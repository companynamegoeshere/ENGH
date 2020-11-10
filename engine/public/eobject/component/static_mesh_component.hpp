#pragma once

#include <eobject/component/primitive_component.hpp>
#include <eobject/data/model_3d.hpp>

namespace ENGH::Render::Component {
class PrimitiveStaticMeshRenderDelegate;
}

namespace ENGH::EObject::Comps {

class StaticMeshComponent : public PrimitiveComponent {
  friend class Render::Component::PrimitiveStaticMeshRenderDelegate;

  Data::Model3D model;
public:
  explicit StaticMeshComponent(Data::Model3D model);

  Render::Component::PrimitiveRenderDelegate *CreateRenderDelegate() override;
};

}
