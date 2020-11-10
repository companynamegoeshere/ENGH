#include <render/component/primitive_static_mesh_render_delegate.hpp>

#include <platform/render/program_shader.hpp>

namespace ENGH::Render::Component {

using ENGH::EObject::Comps::StaticMeshComponent;

PrimitiveStaticMeshRenderDelegate::PrimitiveStaticMeshRenderDelegate(StaticMeshComponent *component) :
    PrimitiveRenderDelegate(component) {
}

void PrimitiveStaticMeshRenderDelegate::WriteCommandBuffer(const RenderDispatcherProxy &proxy) {
  auto *comp = dynamic_cast<StaticMeshComponent *>(primitive);
  proxy.Dispatch(
      RenderCommand{
          static_cast<size_t>(-1),
          comp->model.vertex,
          comp->model.index,
          Platform::Render::BufferLayout{
              {"a_Position", Platform::Render::BufferDataTypes::FLOAT3}
          },
          Platform::Render::ProgramShader::DEBUG_SHADER.get(),
          [&](auto *shader) {
            auto out = proxy.MatrixTransformer(this->primitive->GetWorldMatrix());
            shader->SetUniformMat4("transform", &out[0], true);
          }
      }
  );
}

}
