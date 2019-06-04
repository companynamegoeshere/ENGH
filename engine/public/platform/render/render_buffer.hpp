#pragma once

#include <core/engine.hpp>

namespace ENGH::Platform::Render {

class RenderBuffer {
public:

    virtual void Bind() = 0;

    virtual void Unbind() = 0;

    virtual ~RenderBuffer() = 0;
};

}