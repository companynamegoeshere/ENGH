#pragma once

#include <eobject/component/scene_component.hpp>

namespace ENGH::Render::Component {
class PrimitiveRenderDelegate;
}

namespace ENGH::EObject::Comps {

class PrimitiveComponent : public SceneComponent {
  friend class Render::Component::PrimitiveRenderDelegate;
protected:
  Render::Component::PrimitiveRenderDelegate *renderDelegate = nullptr;

  bool isRenderDirty = true;
public:

  ~PrimitiveComponent() override;

  virtual Render::Component::PrimitiveRenderDelegate *CreateRenderDelegate();

  void RegisterWorldFunctions() override;
};

}
