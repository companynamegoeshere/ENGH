#pragma once

#include <platform/render/buffer_layout.hpp>
#include <platform/render/program_shader.hpp>
#include <platform/render/vertex_array.hpp>

namespace ENGH::Render {

struct RenderCommand {
  Platform::Render::VertexArray *data;
  Platform::Render::ProgramShader *shader;
  std::function<void(Platform::Render::ProgramShader * )> setupUniforms;
};

}
