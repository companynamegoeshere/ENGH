#pragma once

#include <core/math.hpp>
#include <render/render_command.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

class RenderDispatcher {
protected:
  std::function<Math::Mat4(Math::Mat4)> transformer;
public:
  virtual void Dispatch(RenderCommand command) = 0;

  inline const std::function<Math::Mat4(Math::Mat4)> &GetMatrixTransformer() const { return transformer; }

};

}
