#include <render/world_renderer.hpp>
#include <eobject/actor.hpp>

#include <render/component/primitive_render_delegate.hpp>

namespace ENGH::Render {

WorldRenderer::WorldRenderer(
    EObject::World::World *world,
    const std::shared_ptr<Platform::Render::RenderContext> &context
) : world(world),
    context(context),
    renderDispatcher(context) {
  proxy = renderDispatcher.GetProxy(&renderData);
}

void WorldRenderer::SetupRender(Camera::Camera *camera) {
  renderData.camera = camera;
  renderData.projection = camera->GetProjection();
  renderData.view = camera->GetView();

  auto &registry = this->world->registry;
  for (const auto &p : registry.primitives) {
    if (p->IsDirty()) {
      p->UnDirty();
      p->WriteCommandBuffer(*proxy);
    }
  }
}

void WorldRenderer::Render() {
  const auto &color = world->ClearColor;
  context->GetRenderer()->Clear(color.x, color.y, color.z, 1.0f);
  renderDispatcher.Render();
}

}
