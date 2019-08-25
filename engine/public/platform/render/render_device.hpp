#pragma once

#include <core/engine.hpp>

namespace ENGH::Platform::Render {

class RenderDevice {
public:

    virtual void Bind() const = 0;

    virtual void Unbind() const = 0;

    virtual ~RenderDevice() = 0;
};

}