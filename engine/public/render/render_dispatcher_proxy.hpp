#pragma once

#include <core/math.hpp>
#include <render/render_command.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

struct RenderDispatcherProxy {
  const smallfun::SmallFun<Math::Mat4(Math::Mat4), sizeof(void *) * 2> MatrixTransformer;
  const smallfun::SmallFun<void(RenderCommand), sizeof(void *) * 2>    Dispatch;
};

}
