#pragma once

#include <platform/opengl/render/render_context.hpp>
#include <platform/window.hpp>

namespace ENGH::Platform::OpenGL {

class GLFWWindow : public Window {
public:
  bool initialized;

  GLFWwindow *nativeWindow{};

  std::shared_ptr<Render::OpenGL::OpenGLRenderContext> context;

public:

  explicit GLFWWindow(Config config);

  ~GLFWWindow() override;

  void Init() override;

  void Loop(RenderCallback) override;

  std::shared_ptr<Render::RenderContext> GetContext() const override;

};

}