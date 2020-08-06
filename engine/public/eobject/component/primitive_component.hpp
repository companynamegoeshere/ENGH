#pragma once

#include <eobject/component/scene_component.hpp>

namespace ENGH::Render::Component {
class PrimitiveRenderDelegate;
}

namespace ENGH::EObject::Comps {

class PrimitiveComponent : public SceneComponent {
protected:
  Render::Component::PrimitiveRenderDelegate *renderDelegate = nullptr;
public:
  virtual Render::Component::PrimitiveRenderDelegate *CreateRenderDelegate();
};

}
