#include <eobject/component/sphere_component.hpp>
#include <eobject/render/sphere.hpp>
#include <eobject/render/standard_render.hpp>
#include <eobject/render/standard_shaders.hpp>

using ENGH::EObject::Render::Sphere;
using ENGH::EObject::Render::StandardRender;
using ENGH::EObject::Render::StandardShaders;
using ENGH::Platform::Render::ProgramShader;
using ENGH::Render::RenderCommand;

void ENGH::EObject::Comps::SphereComponent::Render(ENGH::Render::RenderDispatcher &dispatcher) const {
  Component::Render(dispatcher);
  StandardRender::Get().RenderStaticMesh(
      *this,
      dispatcher,
      Sphere::Get().array.get(),
      StandardShaders::Get().flatColor.get()
  );
}
