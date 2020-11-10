#pragma once

#include <render/component/primitive_render_delegate.hpp>
#include <eobject/component/box_component.hpp>

namespace ENGH::Render::Component {

class PrimitiveBoxRenderDelegate : public PrimitiveRenderDelegate {
public:
  explicit PrimitiveBoxRenderDelegate(ENGH::EObject::Comps::BoxComponent *component);

private:

  void WriteCommandBuffer(const RenderDispatcherProxy &proxy) override;
};

}