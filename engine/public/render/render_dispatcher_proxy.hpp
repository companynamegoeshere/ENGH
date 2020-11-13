#pragma once

#include <core/math.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>
#include <render/render_command.hpp>
#include <render/camera/camera.hpp>

namespace ENGH::Render {

struct RenderData {
  Math::Mat4 projection;
  Math::Mat4 view;
  ENGH::Render::Camera::Camera *camera;
};

struct RenderDispatcherProxy {
  const RenderData *data;
  const smallfun::SmallFun<size_t(const RenderCommand &), sizeof(void *) * 2> Dispatch;

//  const smallfun::SmallFun<void(size_t id), sizeof(void *) * 2> Remove; // TODO Implements this
  const smallfun::SmallFun<void(size_t id, const TArray<float> &), sizeof(void *) * 2> UpdateData;
  const smallfun::SmallFun<void(size_t id, const TArray<uint32> &), sizeof(void *) * 2> UpdateIndex;
};

}
