#include <platform/opengl/render/fragment_shader.hpp>
#include <platform/opengl/render/program_shader.hpp>
#include <platform/opengl/render/vertex_shader.hpp>

using namespace ENGH::Platform::Render::OpenGL::Shader;

OpenGLProgramShader::OpenGLProgramShader() {
  program = glCreateProgram();
}

OpenGLProgramShader::~OpenGLProgramShader() {
  glDeleteProgram(program);
}

void OpenGLProgramShader::Bind() const {
  glUseProgram(program);
}

void OpenGLProgramShader::Unbind() const {
  glUseProgram(0);
}

void OpenGLProgramShader::Attach(const OpenGLVertexShader &vertShader,
                                 const OpenGLFragmentShader &fragShader) {
  vertShader.Attach(program);
  fragShader.Attach(program);
  glLinkProgram(program);

  GLint success;
  if (!(glGetProgramiv(program, GL_LINK_STATUS, &success), success)) {
    ENGH_CORE_WARN("could not link shader");
  }
  int logLength;
  if ((glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength), logLength) > 0) {
    std::string msg;
    msg.resize(logLength + 1);
    GLint length;
    glGetProgramInfoLog(program, logLength, &length, &msg[0]);
    ENGH_CORE_WARN(msg);
  }

  fragShader.Detach(program);
  vertShader.Detach(program);
}

void OpenGLProgramShader::SetUniformFloat(const std::string &name, const float value) {
  GLint loc = glGetUniformLocation(program, name.c_str());
  glUniform1f(loc, value);
}

void OpenGLProgramShader::SetUniformVec3(const std::string &name, const float v0, const float v1, const float v2) {
  GLint loc = glGetUniformLocation(program, name.c_str());
  glUniform3f(loc, v0, v1, v2);
}

void OpenGLProgramShader::SetUniformMat4(const std::string &name, const float *values, bool transpose) {
  GLint loc = glGetUniformLocation(program, name.c_str());
  glUniformMatrix4fv(loc, 1, transpose ? GL_TRUE : GL_FALSE, values);
}
