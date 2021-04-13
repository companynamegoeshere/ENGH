#include <eobject/component/box_component.hpp>

#include <array>

using namespace ENGH::Render;
using namespace ENGH::Render::Component;
using namespace ENGH::Math;

namespace ENGH::EObject::Comps {

static TArray<float> data;
static TArray<uint32> indexes;

Render::Component::PrimitiveRenderDelegate *BoxComponent::CreateRenderDelegate() {
  class Render : public PrimitiveRenderDelegate {
  public:
    size_t id = -1;

    explicit Render(ENGH::EObject::Comps::BoxComponent *component) : PrimitiveRenderDelegate(component) {
      if (data.empty()) {
        uint32 count = 0;
        for (float j = -1.0f; j <= 1.0f;) {
          for (int i = 0; i < 3; i++) {
            Vec3 n(0.0f);
            n[i] = static_cast<float>(-j);
            size_t p1 = i == 0 ? 1 : 0;
            size_t p2 = i == 2 ? 1 : 2;
            for (int k = 0; k < 4; k++) {
              Vec3 v(j);
              v[p1] = k % 2 != 0 ? -j : j;
              v[p2] = k / 2 != 0 ? -j : j;
              data += {v.x, v.y, v.z, n.x, n.y, n.z};
            }
            indexes += {count, count + 1, count + 2, count + 1, count + 3, count + 2};
            count += 4;
          }
          j += 2.0f;
        }
      }
    }

    void WriteCommandBuffer(const RenderDispatcherProxy &proxy) override {
      id = proxy.Dispatch(
          RenderCommand{
              id,
              data,
              indexes,
              Platform::Render::BufferLayout{
                  {"a_Position", Platform::Render::BufferDataTypes::FLOAT3},
                  {"a_Normal", Platform::Render::BufferDataTypes::FLOAT3}
              },
              Platform::Render::ProgramShader::DEBUG_SHADER.get(),
              [&](auto *shader) {
                SetupStandardUniforms(*shader, proxy);
              }
          }
      );
    }
  };
  return new Render(this);
}

}
