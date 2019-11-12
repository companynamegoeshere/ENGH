#pragma once

#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

struct RenderCommand {
  std::shared_ptr<Platform::Render::VertexArray> data;
  std::shared_ptr<Platform::Render::ProgramShader> shader;
  // TODO Uniforms
};

class RenderDispatcher {
  virtual void Dispatch(RenderCommand command) = 0;
};

}
