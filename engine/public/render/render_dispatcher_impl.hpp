#pragma once

#include <platform/render/render_context.hpp>
#include <render/render_command.hpp>

namespace ENGH::Render {

class RenderDispatcherImpl : public RenderDispatcher {

  std::shared_ptr<Platform::Render::RenderContext> context;
  TArray<RenderCommand> queue;

public:

  RenderDispatcherImpl(std::shared_ptr<Platform::Render::RenderContext> renderer);

  void Dispatch(RenderCommand command);

  void Render();

  inline void SetView(Math::Mat4 view) { this->view = view; }

  inline void SetProjection(Math::Mat4 projection) { this->projection = projection; }

};

}
