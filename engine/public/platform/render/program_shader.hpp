#pragma once

#include "render_device.hpp"

namespace ENGH::Platform::Render {

class ProgramShader : public RenderDevice {
public:
  static std::shared_ptr<ProgramShader> DEBUG_SHADER;

  virtual void SetUniformFloat(const std::string &name, const float value) = 0;

  virtual void SetUniformVec3(const std::string &name, const float v0, const float v1, const float v2) = 0;

  virtual void SetUniformMat4(const std::string &name, const float *values, bool transpose = false) = 0;

};

}