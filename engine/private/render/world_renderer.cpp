#include <render/world_renderer.hpp>
#include <eobject/actor.hpp>

#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::Render {

WorldRenderer::WorldRenderer(EObject::World::World *world,
                             const std::shared_ptr<Platform::Render::RenderContext>& context)
    : world(world),
      context(context),
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
  const auto &color = world->ClearColor;
  context->GetRenderer()->Clear(color.x, color.y, color.z, 1.0f);
  renderDispatcher.Render();
}

}
