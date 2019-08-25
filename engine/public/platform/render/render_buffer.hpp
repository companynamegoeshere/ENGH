#pragma once

#include <core/engine.hpp>

namespace ENGH::Platform::Render {

class RenderBuffer {
public:

    virtual void Bind() const = 0;

    virtual void Unbind() const = 0;

    virtual ~RenderBuffer() = 0;
};

}