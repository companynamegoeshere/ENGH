#pragma once

#include <platform/opengl/glfw_input_provider.hpp>
#include <platform/opengl/render/render_context.hpp>
#include <platform/window.hpp>

namespace ENGH::Platform::OpenGL {

class GLFWWindow : public Window {
  double frameTime;
public:
  bool initialized;

  GLFWwindow *nativeWindow{};

  GLFWInputProvider inputProvider;
  std::shared_ptr<Render::OpenGL::OpenGLRenderContext> context;

public:

  explicit GLFWWindow(Config config);

  ~GLFWWindow() override;

  void Init() override;

  void StartLoop() override;

  bool IsOpen() override;

  std::pair<double, double> GetSize() override;

  double GetFrameTime() override;

  const Input::InputProvider *GetInputProvider() const override;

  std::shared_ptr<Render::RenderContext> GetContext() const override;

};

}