#pragma once

#include <utility>

#include <platform/render/vertex_buffer.hpp>
#include <platform/opengl/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLVertexBuffer : public VertexBuffer {
    GLuint            vbo;
    BufferLayoutEntry layout;
public:

    OpenGLVertexBuffer();

    ~OpenGLVertexBuffer() override;

    void Bind() const override;

    void Unbind() const override;

    void SetData(const TArray<float> &data) override;

    void SetLayout(const BufferLayoutEntry &layout) override;
};

}
