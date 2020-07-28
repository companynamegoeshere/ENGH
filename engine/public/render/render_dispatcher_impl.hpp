#pragma once

#include <platform/render/render_context.hpp>
#include <render/render_command.hpp>

namespace ENGH::Render {

class RenderDispatcherImpl : public RenderDispatcher {

  std::shared_ptr<Platform::Render::RenderContext> context;
  TArray<RenderCommand> queue;
  TArray<std::function<void()>> toCall;

public:

  RenderDispatcherImpl(std::shared_ptr<Platform::Render::RenderContext> renderer, std::function<Math::Mat4(Math::Mat4)> transformer);

  void Dispatch(RenderCommand command) override;

  void Enqueue(std::function<void()> target) override;

  void Render();


};

}
