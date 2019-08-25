#pragma once

#include <core/engine.hpp>
#include <platform/render/index_buffer.hpp>
#include <platform/render/vertex_buffer.hpp>

namespace ENGH::Platform::Render {

enum class RenderLibrary {
    NONE,
    OPENGL
};

class RenderContext {
public:

    virtual void Setup() = 0;

    virtual void SwapBuffers() = 0;

    virtual void Clear(float r, float g, float b, float a) = 0;

    virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer() = 0;

    virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer() = 0;

    // virtual std::shared_ptr <RenderShader> CreateShader(std::string_view vertex, std::string_view fragment) = 0;

    virtual ~RenderContext() = 0;

};

}
