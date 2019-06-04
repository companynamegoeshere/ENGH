#pragma once

#include <utility>

#include <platform/render/index_render_buffer.hpp>
#include <platform/opengl/render/opengl_render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLIndexRenderBuffer : public IndexRenderBuffer {
    GLuint id;
public:

    OpenGLIndexRenderBuffer();

    ~OpenGLIndexRenderBuffer() override;

    void Bind() override;

    void Unbind() override;

    void SetData(TArray<uint32> data) override;
};

}
