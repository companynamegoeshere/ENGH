#pragma once

#include <platform/render/render_context.hpp>

namespace ENGH::Render {

class RenderDispatcherImpl : public RenderDispatcher {

  std::shared_ptr<Platform::Render::RenderContext> context;
  TArray<RenderCommand> queue;

public:

  RenderDispatcherImpl(std::shared_ptr<Platform::Render::RenderContext> renderer);

  void Dispatch(RenderCommand command);

  void Render();

};

}
