#pragma once

#include <utility>

#include <platform/render/vertex_render_buffer.hpp>
#include <platform/opengl/render/opengl_render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLVertexRenderBuffer : public VertexRenderBuffer {
    GLuint id;
public:

    OpenGLVertexRenderBuffer();

    ~OpenGLVertexRenderBuffer() override;

    void Bind() override;

    void Unbind() override;

    void SetData(TArray<float> data) override;
};

}
