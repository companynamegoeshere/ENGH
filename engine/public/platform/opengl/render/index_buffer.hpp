#pragma once

#include <utility>

#include <platform/render/index_buffer.hpp>
#include <platform/opengl/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLIndexBuffer : public IndexBuffer {
    GLuint ibo;
public:

    OpenGLIndexBuffer();

    ~OpenGLIndexBuffer() override;

    void Bind() const override;

    void Unbind() const override;

    void SetData(const TArray<uint32> &data) override;
};

}
