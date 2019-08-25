#pragma once

#include "render_device.hpp"

namespace ENGH::Platform::Render {

class ProgramShader : public RenderDevice {
public:

    virtual void SetUniformFloat(const std::string &name, float value) = 0;

};

}