#pragma once

#include <platform/opengl/render/renderer.hpp>
#include <platform/render/render_context.hpp>
#include <platform/opengl/render/frame_buffer.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLRenderContext : public RenderContext {
  GLFWwindow *window;
  std::shared_ptr<OpenGLRenderer> renderer;
  std::shared_ptr<OpenGLFrameBuffer> screenFrameBuffer;
public:
    explicit OpenGLRenderContext(GLFWwindow *window);

    void Setup() override;

  void SwapBuffers() override;

  std::shared_ptr<IndexBuffer> CreateIndexBuffer() override;

  std::shared_ptr<VertexBuffer> CreateVertexBuffer() override;

  std::shared_ptr<VertexArray> CreateVertexArray() override;

  std::shared_ptr<ProgramShader> CreateShader(const std::string &vertex, const std::string &fragment) override;

  std::shared_ptr<FrameBuffer> CreateFrameBuffer(FrameBuffer::BufferType type, uint32 width, uint32 height) override;

  std::shared_ptr<FrameBuffer> GetScreenFrameBuffer() override;

  std::shared_ptr<Renderer> GetRenderer() override;

  ~OpenGLRenderContext() override;

};

}
