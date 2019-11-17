#include <eobject/component/box_component.hpp>
#include <eobject/render/box.hpp>
#include <eobject/render/standard_shaders.hpp>

using ENGH::EObject::Render::Box;
using ENGH::EObject::Render::StandardShaders;
using ENGH::Render::RenderCommand;
using ENGH::Platform::Render::ProgramShader;

void ENGH::EObject::Comps::BoxComponent::Render(ENGH::Render::RenderDispatcher &dispatcher) const {
  Component::Render(dispatcher);
  auto transform = this->transform;
  dispatcher.Dispatch(
      {
          Box::INSTANCE->array.get(),
          StandardShaders::INSTANCE->flatColor.get(),
          [transform, &dispatcher](ProgramShader *shader) {
            auto out = dispatcher.GetProjection() * dispatcher.GetView() * transform.ToMatrix();
            shader->SetUniformMat4("transform", &out[0], true);
          }
      }
  );
}
