#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <platform/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLRenderContext : public RenderContext {
    GLFWwindow *window;
public:
    explicit OpenGLRenderContext(GLFWwindow *window);

    void Setup() override;

    void SwapBuffers() override;

    void Clear(float r, float g, float b, float a) override;

    std::shared_ptr<IndexBuffer> CreateIndexBuffer() override;

    std::shared_ptr<VertexBuffer> CreateVertexBuffer() override;

    ~OpenGLRenderContext() override;

};

}
