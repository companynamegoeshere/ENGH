#pragma once

#include <eobject/component/component.hpp>
#include <eobject/world/world.hpp>
#include <render/camera/camera.hpp>
#include <render/render_dispatcher_impl.hpp>

namespace ENGH::Render {

class WorldRenderer {

  EObject::World::World *world;

  Math::Mat4 cameraProjectionCache;
  Math::Mat4 cameraViewCache;

  RenderDispatcherImpl renderDispatcher;

  Math::Mat4 Transformer(Math::Mat4 original);

  void RenderComponent(EObject::Comps::Component *);

public:
  WorldRenderer(EObject::World::World *world, std::shared_ptr<Platform::Render::RenderContext> context);

  void SetupRender(Camera::Camera *camera);

  inline RenderDispatcherImpl &GetDispatcher() { return renderDispatcher; }

};

}
