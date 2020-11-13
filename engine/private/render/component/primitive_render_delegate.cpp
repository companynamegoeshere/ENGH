#include <render/component/primitive_render_delegate.hpp>

#include <eobject/component/primitive_component.hpp>

namespace ENGH::Render::Component {

void PrimitiveRenderDelegate::SetupStandardUniforms(
    Platform::Render::ProgramShader &shader,
    const RenderDispatcherProxy &proxy
) {
  shader.SetUniformMat4("projection", &proxy.data->projection[0]);
  shader.SetUniformMat4("view", &proxy.data->view[0]);
  Math::Vec3 &pos = proxy.data->camera->position;
  shader.SetUniformVec3("cameraPos", pos.x, pos.y, pos.z);
  shader.SetUniformMat4("transform", &primitive->GetWorldMatrix()[0]);
}

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
