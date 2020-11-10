#pragma once

#include <platform/render/buffer_layout.hpp>
#include <platform/render/program_shader.hpp>
#include <platform/render/index_buffer.hpp>
#include <platform/render/vertex_array.hpp>

namespace ENGH::Render {

struct RenderCommand {
  size_t id = -1;
  TArray<float> data;
  TArray<uint32> index;
  Platform::Render::BufferLayout layout;
  Platform::Render::ProgramShader *shader;
  smallfun::SmallFun<void(Platform::Render::ProgramShader * ), 32> setupUniforms;
};

}
