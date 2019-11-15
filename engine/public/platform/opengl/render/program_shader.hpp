#pragma once

#include <platform/render/program_shader.hpp>
#include <platform/opengl/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL::Shader {

class OpenGLProgramShader : public ProgramShader {
  GLuint program;
public:

  OpenGLProgramShader();

  ~OpenGLProgramShader() override;

  void Attach(const class OpenGLVertexShader &vertShader, const class OpenGLFragmentShader &fragShader);

  void Bind() const override;

  void Unbind() const override;

private:
  void SetUniformFloat(const std::string &name, const float value) override;

  void SetUniformVec3(const std::string &name, const float v0, const float v1, const float v2) override;

  void SetUniformMat4(const std::string &name, const float *values, bool transpose) override;

};

}