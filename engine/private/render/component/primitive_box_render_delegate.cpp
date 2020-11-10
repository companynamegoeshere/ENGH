#include <render/component/primitive_box_render_delegate.hpp>

#include <platform/render/program_shader.hpp>

namespace ENGH::Render::Component {

//size_t BoxPrimitiveRenderDelegate::id = -1;

PrimitiveBoxRenderDelegate::PrimitiveBoxRenderDelegate(ENGH::EObject::Comps::BoxComponent *component) :
    PrimitiveRenderDelegate(component) {
}

void PrimitiveBoxRenderDelegate::WriteCommandBuffer(const RenderDispatcherProxy &proxy) {
  proxy.Dispatch(
      RenderCommand{
          static_cast<size_t>(-1),
          {
              -1.0f, -1.0f, -1.0f, // 0
              +1.0f, -1.0f, -1.0f, // 1
              -1.0f, -1.0f, +1.0f, // 2
              +1.0f, -1.0f, +1.0f, // 3

              -1.0f, +1.0f, -1.0f, // 4
              +1.0f, +1.0f, -1.0f, // 5
              -1.0f, +1.0f, +1.0f, // 6
              +1.0f, +1.0f, +1.0f  // 7
          },
          {
              0, 1, 3, // bottom
              0, 3, 2,

              0, 2, 6, // left
              0, 6, 4,

              0, 4, 5, // back
              0, 5, 1,

              1, 5, 7, // right
              1, 7, 3,

              2, 6, 7, // front
              2, 7, 3,

              4, 5, 7, // top
              4, 7, 6
          },
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
