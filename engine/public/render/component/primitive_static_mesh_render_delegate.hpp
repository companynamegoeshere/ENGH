#pragma once

#include <render/component/primitive_render_delegate.hpp>
#include <eobject/component/static_mesh_component.hpp>

namespace ENGH::Render::Component {

class PrimitiveStaticMeshRenderDelegate : public PrimitiveRenderDelegate {
public:
  explicit PrimitiveStaticMeshRenderDelegate(ENGH::EObject::Comps::StaticMeshComponent *component);

private:

  void WriteCommandBuffer(const RenderDispatcherProxy &proxy) override;
};

}