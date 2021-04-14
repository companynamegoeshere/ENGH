#pragma once

#include <platform/glfw/glfw_input_provider.hpp>
#include <platform/window.hpp>

namespace ENGH::Platform::GLFW {

class Window : public ::ENGH::Platform::Window {
  double totalTime;
  double frameTime;
public:
  bool initialized;

  GLFWwindow *nativeWindow{};

  InputProvider inputProvider;
//  std::shared_ptr<Render::OpenGL::OpenGLRenderContext> context;

  struct UserData {
    Window* window;
    InputProvider* inputProvider;
  };

public:

  Window(filament::Engine *engine, Config config);

  ~Window() override;

  void Init() override;

  void StartLoop() override;

  bool IsOpen() override;

  std::pair<double, double> GetSize() override;

  double GetFrameTime() override;

  double GetTotalTime() override;

  Input::InputProvider *GetInputProvider() override;

//  std::shared_ptr<Render::RenderContext> GetContext() override;

  void* GetNativeHandler() override;

};

}