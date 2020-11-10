#include <eobject/component/sphere_component.hpp>
#include <render/component/primitive_render_delegate.hpp>

using namespace ENGH::Render;
using namespace ENGH::Render::Component;

namespace ENGH::EObject::Comps {

Render::Component::PrimitiveRenderDelegate *SphereComponent::CreateRenderDelegate() {
  class Render : public PrimitiveRenderDelegate {
  public:
    size_t lastId = -1;

    explicit Render(ENGH::EObject::Comps::SphereComponent *component) :
        PrimitiveRenderDelegate(component) {}

    void WriteCommandBuffer(const RenderDispatcherProxy &proxy) override {
      auto *comp = dynamic_cast<SphereComponent *>(primitive);

      TArray<float> dataList;
      TArray<uint32> indexList;

      uint32 lats = comp->latCount;
      uint32 longs = comp->longCount;

      uint32 index = 0;
      for (uint32 i = 0; i <= lats; i++) {
        for (uint32 j = 0; j <= longs; j++) {
          float longPi = Mathf::PI2 * j / longs;
          float latPi = Mathf::PI * i / lats;
          dataList += {
              std::sin(latPi) * std::cos(longPi),
              std::sin(latPi) * std::sin(longPi),
              std::cos(latPi)
          };
          indexList += index++;
        }
      }

      lastId = proxy.Dispatch(
          RenderCommand{
              lastId,
              dataList,
              indexList,
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
  };
  return new Render(this);
}

}
