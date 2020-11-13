#pragma once

#include <platform/opengl/render/program_shader.hpp>
#include <platform/opengl/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL::Shader {

class BaseShader {
protected:
    GLuint shaderId;
    bool success;
public:
    BaseShader(GLenum type, const std::string &data);

    ~BaseShader();

    void Attach(const GLuint program) const;

    void Detach(const GLuint program) const;

    inline bool CompiledSuccess() const { return success; }
};

}
