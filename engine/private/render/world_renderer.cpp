#include <render/world_renderer.hpp>
#include <eobject/actor.hpp>

#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::Render {

WorldRenderer::WorldRenderer(EObject::World::World *world,
                             std::shared_ptr<Platform::Render::RenderContext> context)
    : world(world),
      renderDispatcher(
          context,
          [this](Math::Mat4 o) {
            return cameraProjectionCache * cameraViewCache * o;
          }
      ) {}

void WorldRenderer::SetupRender(Camera::Camera *camera) {
  cameraProjectionCache = camera->GetProjection();
  cameraViewCache       = camera->GetView();

  auto            &registry = this->world->registry;
  for (const auto &p : registry.primitives) {
    if(p->IsDirty()) {

    }
  }
}

void WorldRenderer::Render() {
  renderDispatcher.Render();
}

}
