#pragma once

#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

struct RenderCommand {
  Platform::Render::VertexArray *data;
  Platform::Render::ProgramShader *shader;
  // TODO Uniforms
};

class RenderDispatcher {
public:
  virtual void Dispatch(RenderCommand command) = 0;
};

}
