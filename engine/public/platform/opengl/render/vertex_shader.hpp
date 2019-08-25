#pragma once

#include <platform/opengl/render/base_shader.hpp>

namespace ENGH::Platform::Render::OpenGL::Shader {

class OpenGLVertexShader : public BaseShader {
public:
    OpenGLVertexShader(const std::string &data);
};

}
