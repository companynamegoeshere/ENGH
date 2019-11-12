#pragma once

#include <eobject/world.hpp>
#include <render/render_dispatcher_impl.hpp>

namespace ENGH::Render {

class WorldRenderer {
  EObject::World *world;
  RenderDispatcherImpl renderDispatcher;

  void RenderComponent(EObject::Component *);

public:
  WorldRenderer(EObject::World *world, std::shared_ptr<Platform::Render::RenderContext> context);

  void SetupRender();

  void Render();
};

}
