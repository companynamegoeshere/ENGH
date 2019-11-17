#include <render/world_renderer.hpp>
#include <eobject/actor.hpp>
#include <eobject/render/renderable_object.hpp>

ENGH::Render::WorldRenderer::WorldRenderer(EObject::World *world, std::shared_ptr<Platform::Render::RenderContext> context)
    : world(world), renderDispatcher(context) {
  Platform::Render::RenderContext &contextRef = *context.get();
  for (auto &data : EObject::Render::RenderableObject::GetList()) {
    data->SetupRender(contextRef);
  }
}

void ENGH::Render::WorldRenderer::RenderComponent(EObject::Comps::Component *comp) {
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
