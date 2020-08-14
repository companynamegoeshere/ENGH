#pragma once

namespace ENGH::EObject::Comps {
class PrimitiveComponent;
}

namespace ENGH::Render::Component {

class PrimitiveRenderDelegate {
  friend class EObject::Comps::PrimitiveComponent;
  EObject::Comps::PrimitiveComponent *primitive;
public:
  PrimitiveRenderDelegate(EObject::Comps::PrimitiveComponent *primitive);

  virtual ~PrimitiveRenderDelegate() = 0;

  virtual bool IsDirty();
};

}