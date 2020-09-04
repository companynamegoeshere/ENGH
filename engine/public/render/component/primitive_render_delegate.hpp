#pragma once

namespace ENGH::EObject::Comps {
class PrimitiveComponent;
}

namespace ENGH::Render {
class WorldRenderer;
}

namespace ENGH::Render::Component {

class PrimitiveRenderDelegate {
  friend class EObject::Comps::PrimitiveComponent;
  friend class ENGH::Render::WorldRenderer;

  EObject::Comps::PrimitiveComponent *primitive;
public:
  PrimitiveRenderDelegate(EObject::Comps::PrimitiveComponent *primitive);

  virtual ~PrimitiveRenderDelegate() = 0;

  virtual bool IsDirty();

  virtual void WriteCommandBuffer();
};

}