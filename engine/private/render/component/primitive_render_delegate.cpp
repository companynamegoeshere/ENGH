#include <render/component/primitive_render_delegate.hpp>

#include <eobject/component/primitive_component.hpp>

namespace ENGH::Render::Component {

PrimitiveRenderDelegate::PrimitiveRenderDelegate(ENGH::EObject::Comps::PrimitiveComponent *primitive) :
    primitive(primitive) {

}

PrimitiveRenderDelegate::~PrimitiveRenderDelegate() {}

bool PrimitiveRenderDelegate::IsDirty() {
  return primitive == nullptr || primitive->isRenderDirty;
}

}
