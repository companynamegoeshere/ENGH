#pragma once

#include <platform/opengl/render/renderer.hpp>
#include <platform/render/render_context.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLRenderContext : public RenderContext {
  GLFWwindow *window;
  std::shared_ptr<OpenGLRenderer> renderer;
public:
    explicit OpenGLRenderContext(GLFWwindow *window);

    void Setup() override;

  void SwapBuffers() override;

  std::shared_ptr<IndexBuffer> CreateIndexBuffer() override;

  std::shared_ptr<VertexBuffer> CreateVertexBuffer() override;

  std::shared_ptr<VertexArray> CreateVertexArray() override;

  std::shared_ptr<ProgramShader> CreateShader(const std::string &vertex, const std::string &fragment) override;

  std::shared_ptr<Renderer> GetRenderer() override;

  ~OpenGLRenderContext() override;

};

}
