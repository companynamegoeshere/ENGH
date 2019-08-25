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
    if(!(glGetProgramiv(program, GL_LINK_STATUS, &success), success)) {
        ENGH_CORE_WARN("could not link shader");
    }
    int logLength;
    if ((glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength), logLength) > 0) {
        std::string msg;
        msg.resize(logLength + 1);
        glGetProgramInfoLog(program, logLength, nullptr, msg.data());
        ENGH_CORE_WARN(msg);
    }

    fragShader.Detach(program);
    vertShader.Detach(program);
}

void OpenGLProgramShader::SetUniformFloat(const std::string &name, float value) {
    GLint loc = glGetUniformLocation(program, name.c_str());
    glUniform1f(loc, value);
}
