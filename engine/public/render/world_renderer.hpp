#pragma once

#include <eobject/world.hpp>
#include <render/camera/camera.hpp>
#include <render/render_dispatcher_impl.hpp>
#include <eobject/component/component.hpp>

namespace ENGH::Render {

class WorldRenderer {

  EObject::World::World *world;

  Camera::Camera *camera;
  Math::Mat4 cameraProjectionCache;
  Math::Mat4 cameraViewCache;

  RenderDispatcherImpl renderDispatcher;

  Math::Mat4 Transformer(Math::Mat4 original);

  void RenderComponent(EObject::Comps::Component *);

public:
  WorldRenderer(EObject::World::World *world, Camera::Camera *camera, std::shared_ptr<Platform::Render::RenderContext> context);

  void SetupRender();

  inline RenderDispatcherImpl &GetDispatcher() { return renderDispatcher; }

};

}
