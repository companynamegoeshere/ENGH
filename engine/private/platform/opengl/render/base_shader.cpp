#pragma

#include <platform/opengl/render/base_shader.hpp>

using namespace ENGH::Platform::Render::OpenGL::Shader;

BaseShader::BaseShader(GLenum type, const std::string &data) {
    shaderId = glCreateShader(type);
    const GLchar *src = data.c_str();
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);
#ifdef ENGH_DEV
    GLint result = GL_FALSE;
    if (! (glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result), result)) {
        ENGH_CORE_WARN("could not compile ", type == GL_VERTEX_SHADER ? "vertex" : "frag", " shader");
    }
    int logLength;
    if ((glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength), logLength) > 0) {
        std::string msg;
        msg.resize(logLength + 1);
        glGetShaderInfoLog(shaderId, logLength, nullptr, msg.data());
        ENGH_CORE_WARN(msg);
    }
#endif
}

BaseShader::~BaseShader() {
    glDeleteShader(shaderId);
}

void BaseShader::Attach(const GLuint program) const {
    glAttachShader(program, shaderId);
}

void BaseShader::Detach(const GLuint program) const {
    glDetachShader(program, shaderId);
}
