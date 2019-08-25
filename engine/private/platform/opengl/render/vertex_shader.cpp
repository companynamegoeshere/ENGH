#include <platform/opengl/render/vertex_shader.hpp>

ENGH::Platform::Render::OpenGL::Shader::OpenGLVertexShader::OpenGLVertexShader(const std::string &data)
        : BaseShader(GL_VERTEX_SHADER, data) {
}
