#include <render/world_renderer.hpp>
#include <eobject/component/component.hpp>

ENGH::Render::WorldRenderer::WorldRenderer(EObject::World *world, std::shared_ptr<Platform::Render::RenderContext> context)
    : world(world), renderDispatcher(context) {
}

void ENGH::Render::WorldRenderer::RenderComponent(EObject::Component *comp) {
  comp->Render(this->renderDispatcher);
  for (const auto &child : comp->children) {
    this->RenderComponent(child);
  }
}

void ENGH::Render::WorldRenderer::SetupRender() {
  for (const auto &actor : this->world->actorList) {
    this->RenderComponent(actor->GetRoot());
  }
}

void ENGH::Render::WorldRenderer::Render() {
  this->renderDispatcher.Render();
}

