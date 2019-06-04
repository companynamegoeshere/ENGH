#pragma once

#include <core/engine.hpp>
#include <platform/render/index_render_buffer.hpp>
#include <platform/render/vertex_render_buffer.hpp>

enum class RenderLibrary {
    NONE,
    OPENGL
};

namespace ENGH::Platform::Render {

class RenderContext {
public:

    virtual void Setup() = 0;

    virtual void SwapBuffers() = 0;

    virtual std::shared_ptr <IndexRenderBuffer> CreateIndexBuffer() = 0;

    virtual std::shared_ptr <VertexRenderBuffer> CreateVertexBuffer() = 0;

    // virtual std::shared_ptr <RenderShader> CreateShader(std::string_view vertex, std::string_view fragment) = 0;

    virtual ~RenderContext() = 0;

};

}
