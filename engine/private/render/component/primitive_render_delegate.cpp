#include <render/component/primitive_render_delegate.hpp>

#include <eobject/component/primitive_component.hpp>

namespace ENGH::Render::Component {

PrimitiveRenderDelegate::PrimitiveRenderDelegate(ENGH::EObject::Comps::PrimitiveComponent *primitive) :
    primitive(primitive) {
}

PrimitiveRenderDelegate::~PrimitiveRenderDelegate() = default;


void PrimitiveRenderDelegate::UnDirty() {
  primitive->isRenderDirty = false;
}

bool PrimitiveRenderDelegate::IsDirty() {
  return primitive->isRenderDirty;
}

}
