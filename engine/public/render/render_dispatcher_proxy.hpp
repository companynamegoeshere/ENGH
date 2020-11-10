#pragma once

#include <core/math.hpp>
#include <render/render_command.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

struct RenderDispatcherProxy {
  const smallfun::SmallFun<Math::Mat4(const Math::Mat4 &), sizeof(void *) * 2> MatrixTransformer;
  const smallfun::SmallFun<size_t(const RenderCommand &), sizeof(void *) * 2> Dispatch;

  const smallfun::SmallFun<void(size_t id, const TArray<float> &), sizeof(void *) * 2> UpdateData;
  const smallfun::SmallFun<void(size_t id, const TArray<uint32> &), sizeof(void *) * 2> UpdateIndex;
};

}
