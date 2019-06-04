#pragma once

#include <utility>

#include <platform/render/index_render_buffer.hpp>
#include <platform/opengl/render/opengl_render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLIndexRenderBuffer : public IndexRenderBuffer {
    GLuint id;
    GLenum target;
    GLenum usage;
public:

    OpenGLIndexRenderBuffer();

    void Bind() override;

    void Unbind() override;

    ~OpenGLIndexRenderBuffer();
};

}
