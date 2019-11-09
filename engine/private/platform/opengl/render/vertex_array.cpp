#include <platform/opengl/render/vertex_array.hpp>

using ENGH::Platform::Render::BufferDataTypes;

static GLenum BufferDataTypeToGL(const BufferDataTypes &type) {
    auto id = type.GetId();
    if (id == BufferDataTypes::BOOL.GetId()) return GL_BOOL;
    if (id == BufferDataTypes::FLOAT.GetId()) return GL_FLOAT;
    if (id == BufferDataTypes::FLOAT2.GetId()) return GL_FLOAT;
    if (id == BufferDataTypes::FLOAT3.GetId()) return GL_FLOAT;
    if (id == BufferDataTypes::FLOAT4.GetId()) return GL_FLOAT;
    if (id == BufferDataTypes::INT.GetId()) return GL_INT;
    if (id == BufferDataTypes::INT2.GetId()) return GL_INT;
    if (id == BufferDataTypes::INT3.GetId()) return GL_INT;
    if (id == BufferDataTypes::INT4.GetId()) return GL_INT;
    if (id == BufferDataTypes::MAT3.GetId()) return GL_FLOAT;
    if (id == BufferDataTypes::MAT4.GetId()) return GL_FLOAT;
    ENGH_CORE_FATAL("Invalid BufferDataTypes leak (unknown type)");
    return 0;
}

ENGH::Platform::Render::OpenGL::OpenGLVertexArray::OpenGLVertexArray() : offset(0) {
    glGenVertexArrays(1, &vao);
}

ENGH::Platform::Render::OpenGL::OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1, &vao);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexArray::Bind() const {
    glBindVertexArray(vao);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexArray::Unbind() const {
    glBindVertexArray(0);
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
    auto layout  = vertexBuffer->GetLayout();
    auto entries = layout.GetEntries();

#ifdef ENGH_DEBUG
    if (entries.size() == 0) {
        ENGH_CORE_ERROR("Trying to add vertex buffer without layout!");
    }
#endif

    this->Bind();
    vertexBuffer->Bind();

    for (uint32 i = 0; i < entries.size(); i ++) {
        const auto &element = entries[i];
        glEnableVertexAttribArray(i + offset);
        glVertexAttribPointer(
            i + offset,
            element.type.GetCount(),
            BufferDataTypeToGL(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            reinterpret_cast<const void *>(static_cast<uintptr_t>(element.offset))
        );
    }

    this->vertexBuffers.push_back(vertexBuffer);
    this->offset += static_cast<uint32>(entries.size());
}

void ENGH::Platform::Render::OpenGL::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
    this->Bind();
    indexBuffer->Bind();
    this->indexBuffer = indexBuffer;
}

const std::vector<std::shared_ptr<ENGH::Platform::Render::VertexBuffer>> &ENGH::Platform::Render::OpenGL::OpenGLVertexArray::GetVertexBuffers() const {
    return vertexBuffers;
}

const std::shared_ptr<ENGH::Platform::Render::IndexBuffer> &ENGH::Platform::Render::OpenGL::OpenGLVertexArray::GetIndexBuffer() const {
    return indexBuffer;
}
