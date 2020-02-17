#include <eobject/component/box_component.hpp>
#include <eobject/render/box.hpp>
#include <eobject/render/standard_render.hpp>
#include <eobject/render/standard_shaders.hpp>

using ENGH::EObject::Render::Box;
using ENGH::EObject::Render::StandardRender;
using ENGH::EObject::Render::StandardShaders;
using ENGH::Platform::Render::ProgramShader;
using ENGH::Render::RenderCommand;

void ENGH::EObject::Comps::BoxComponent::Render(ENGH::Render::RenderDispatcher &dispatcher) const {
  Component::Render(dispatcher);
  StandardRender::Get().RenderStaticMesh(
      this,
      dispatcher,
      Box::Get().array.get(),
      Box::Get().indexBuffer.get(),
      StandardShaders::Get().flatColor.get()
  );
}
