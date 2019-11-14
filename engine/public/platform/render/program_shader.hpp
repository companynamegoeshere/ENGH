#pragma once

#include "render_device.hpp"

namespace ENGH::Platform::Render {

class ProgramShader : public RenderDevice {
public:

  virtual void SetUniformFloat(const std::string &name, float value) = 0;

  virtual void SetUniformVec3(const std::string &name, float v0, float v1, float v2) = 0;

  virtual void SetUniformMat4(const std::string &name, float *values, bool transpose = false) = 0;

};

}