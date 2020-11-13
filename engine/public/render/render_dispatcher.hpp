#pragma once

#include <platform/render/render_context.hpp>
#include <render/render_command.hpp>

namespace ENGH::Render {

class RenderDispatcher {

  std::shared_ptr<Platform::Render::RenderContext> context;

  struct RenderEntry {
    std::shared_ptr<Platform::Render::VertexArray> vao;
    std::shared_ptr<Platform::Render::IndexBuffer> index;
    Platform::Render::ProgramShader *shader;
    smallfun::SmallFun<void(Platform::Render::ProgramShader *), 32> setupUniforms;
  };

  TArray<RenderEntry> queue;

public:

  RenderDispatcher(std::shared_ptr<Platform::Render::RenderContext> renderer);

  void Render();

  std::unique_ptr<RenderDispatcherProxy> GetProxy(RenderData *);

};

}
