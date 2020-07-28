#include <eobject/component/sphere_component.hpp>
#include <eobject/render/sphere.hpp>
#include <eobject/render/standard_render.hpp>
#include <eobject/render/standard_shaders.hpp>

using ENGH::EObject::Render::Sphere;
using ENGH::EObject::Render::StandardRender;
using ENGH::EObject::Render::StandardShaders;
using ENGH::Platform::Render::ProgramShader;
using ENGH::Render::RenderCommand;
using ENGH::Render::RenderDispatcher;

namespace ENGH::EObject::Comps {

SphereComponent::SphereComponent(uint32 latCount, uint32 longCount) : latCount(latCount), longCount(longCount) {}

void SphereComponent::Render(RenderDispatcher &dispatcher) {
  Component::Render(dispatcher);
  if (lastLat != latCount || lastLong != longCount) {
    lastLat  = latCount;
    lastLong = longCount;
    dispatcher.Enqueue([&]() {
      this->sphere = Sphere::Get(latCount, longCount);
    });
  }
  if(sphere) {
    StandardRender::RenderStaticMesh(
        this,
        dispatcher,
        sphere.get()->array.get(),
        sphere.get()->indexBuffer.get(),
        StandardShaders::Get().flatColor.get()
    );
  }
}

}
