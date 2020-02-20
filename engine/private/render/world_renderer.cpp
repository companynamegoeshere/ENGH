#include <render/world_renderer.hpp>
#include <eobject/actor.hpp>
#include <eobject/render/renderable_object.hpp>

namespace ENGH::Render {

using EObject::Render::RenderableObject;

WorldRenderer::WorldRenderer(EObject::World *world,
                             Camera::Camera *camera,
                             std::shared_ptr<Platform::Render::RenderContext> context)
    : world(world),
      camera(camera),
      renderDispatcher(
          context, [this](auto o) { return this->Transformer(o); }
      ) {
  Platform::Render::RenderContext &contextRef = *(RenderableObject::currentContext = context.get());

  TArray<RenderableObject *> &renderableList = RenderableObject::GetList();
  for (auto &data : renderableList) {
    data->SetupRender(contextRef);
  }
  renderableList.clear();
}

void WorldRenderer::RenderComponent(EObject::Comps::Component *comp) {
  comp->Render(this->renderDispatcher);
  for (const auto &child : comp->children) {
    this->RenderComponent(child);
  }
}

Math::Mat4 WorldRenderer::Transformer(Math::Mat4 original) {
  return cameraProjectionCache * cameraViewCache * original;
}

void WorldRenderer::SetupRender() {
  cameraProjectionCache = camera->GetProjection();
  cameraViewCache       = camera->GetView();
  for (const auto &actor : this->world->actorList) {
    this->RenderComponent(actor->GetRoot());
  }
}

}
