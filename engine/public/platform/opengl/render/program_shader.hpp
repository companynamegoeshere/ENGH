#pragma once

#include <platform/render/program_shader.hpp>
#include <platform/opengl/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL::Shader {

class OpenGLProgramShader : public ProgramShader {
    GLuint program;
public:

    OpenGLProgramShader();

    ~OpenGLProgramShader() override;

    void Attach(const class OpenGLVertexShader& vertShader, const class OpenGLFragmentShader& fragShader);

    void Bind() const override;

    void Unbind() const override;

private:
    void SetUniformFloat(const std::string &name, float value) override;

};

}