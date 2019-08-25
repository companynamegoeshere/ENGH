#pragma once

#include <utility>

#include <platform/render/vertex_array.hpp>
#include <platform/opengl/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLVertexArray : public VertexArray {
    GLuint                                     vao;
    uint32                                     offset;
    std::shared_ptr<IndexBuffer>               indexBuffer;
    std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
public:

    OpenGLVertexArray();

    ~OpenGLVertexArray() override;

    void Bind() const override;

    void Unbind() const override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;

    void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

    const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override;

    const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override;

};

}