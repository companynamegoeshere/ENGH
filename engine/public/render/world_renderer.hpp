#pragma once

#include <eobject/component/component.hpp>
#include <eobject/world/world.hpp>
#include <render/camera/camera.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::Render {

class WorldRenderer {

  EObject::World::World *world;
  std::shared_ptr<Platform::Render::RenderContext> context;
  RenderDispatcher renderDispatcher;
  std::unique_ptr<RenderDispatcherProxy> proxy;

  RenderData renderData;

public:
  WorldRenderer(EObject::World::World *world, const std::shared_ptr<Platform::Render::RenderContext>& context);

  void SetupRender(Camera::Camera *camera);

  void Render();

  inline RenderDispatcherProxy GetDispatcher() { return *proxy; }
};

}
