#pragma once

#include <platform/render/buffer_layout.hpp>
#include <platform/render/program_shader.hpp>
#include <platform/render/index_buffer.hpp>
#include <platform/render/vertex_array.hpp>

namespace ENGH::Render {

struct RenderCommand {
  Platform::Render::VertexArray *data;
  Platform::Render::IndexBuffer *index;
  Platform::Render::ProgramShader *shader;
  smallfun::SmallFun<void(Platform::Render::ProgramShader * ), 1 << 7> setupUniforms;
};

}
