#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::Render::Component {

PrimitiveRenderDelegate::PrimitiveRenderDelegate(ENGH::EObject::Comps::PrimitiveComponent *primitive) :
    primitive(primitive) {

}

PrimitiveRenderDelegate::~PrimitiveRenderDelegate() {}

}
