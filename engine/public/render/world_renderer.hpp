#pragma once

#include <eobject/component/component.hpp>
#include <eobject/world/world.hpp>
#include <render/camera/camera.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::Render {

class WorldRenderer {

  EObject::World::World *world;

  Math::Mat4 cameraProjectionCache;
  Math::Mat4 cameraViewCache;

  RenderDispatcher renderDispatcher;

public:
  WorldRenderer(EObject::World::World *world, std::shared_ptr<Platform::Render::RenderContext> context);

  void SetupRender(Camera::Camera *camera);

  void Render();

  inline RenderDispatcherProxy GetDispatcher() { return renderDispatcher.GetProxy(); }
};

}
