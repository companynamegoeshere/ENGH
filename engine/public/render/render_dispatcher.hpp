#pragma once

#include <platform/render/render_context.hpp>
#include <render/render_command.hpp>

namespace ENGH::Render {

class RenderDispatcher {

  std::shared_ptr<Platform::Render::RenderContext>           context;

  smallfun::SmallFun<Math::Mat4(Math::Mat4), sizeof(void *) * 2> transformer;

  TArray<RenderCommand> queue;

public:

  RenderDispatcher(
      std::shared_ptr<Platform::Render::RenderContext> renderer,
      smallfun::SmallFun<Math::Mat4(Math::Mat4), sizeof(void *) * 2> transformer
  );

  void Render();

  RenderDispatcherProxy GetProxy();

};

}
