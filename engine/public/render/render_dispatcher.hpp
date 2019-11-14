#pragma once

#include <core/math.hpp>
#include <render/render_command.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/program_shader.hpp>

namespace ENGH::Render {

class RenderDispatcher {
public:
  virtual void Dispatch(RenderCommand command) = 0;
};

}
