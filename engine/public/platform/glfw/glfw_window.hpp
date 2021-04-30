#pragma once

#include <platform/glfw/glfw_input_provider.hpp>
#include <platform/window.hpp>

namespace filament {
class SwapChain;
};

namespace ENGH::Platform {
class ECore;
}
namespace ENGH::Platform::GLFW {

class Window : public ::ENGH::Platform::Window {
  double totalTime;
  double frameTime;

  bool initialized;

  GLFWwindow *glfwWindow{};

  uint width, height;

public:

  InputProvider inputProvider;

  struct UserData {
    Window& window;
    InputProvider& inputProvider;
  };

public:

  Window(ECore *engh, Config config);

  ~Window() override;

  void Init() override;

  void StartLoop() override;

  bool IsOpen() override;

  std::pair<double, double> GetSize() override;

  double GetFrameTime() override;

  double GetTotalTime() override;

  Input::InputProvider *GetInputProvider() override;

  void* GetNativeHandler() override;

private:

  void doResize(int width, int height);

};

}