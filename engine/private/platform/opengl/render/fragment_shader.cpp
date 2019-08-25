#include <platform/opengl/render/fragment_shader.hpp>

ENGH::Platform::Render::OpenGL::Shader::OpenGLFragmentShader::OpenGLFragmentShader(const std::string &data)
        : BaseShader(GL_FRAGMENT_SHADER, data) {
}
