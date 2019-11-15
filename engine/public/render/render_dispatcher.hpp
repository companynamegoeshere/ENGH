#pragma once

#include <core/math.hpp>
#include <render/render_command.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

class RenderDispatcher {
protected:
  Math::Mat4 view;
  Math::Mat4 projection;
public:
  virtual void Dispatch(RenderCommand command) = 0;

  inline const Math::Mat4 &GetView() const { return view; }

  inline const Math::Mat4 &GetProjection() const { return projection; }
};

}
