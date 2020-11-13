#pragma once

#include <render/render_dispatcher_proxy.hpp>

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
protected:
  EObject::Comps::PrimitiveComponent *primitive;
public:

  explicit PrimitiveRenderDelegate(EObject::Comps::PrimitiveComponent *primitive);

  virtual ~PrimitiveRenderDelegate() = 0;

  virtual void UnDirty();

  virtual bool IsDirty();

  virtual void WriteCommandBuffer(const RenderDispatcherProxy &proxy) = 0;

  void SetupStandardUniforms(Platform::Render::ProgramShader&, const RenderDispatcherProxy&);
};

}