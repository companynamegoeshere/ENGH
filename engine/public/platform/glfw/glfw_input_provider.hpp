#pragma once

#include <input/input_provider.hpp>

#include <map>

struct GLFWwindow;

namespace ENGH::Platform::GLFW {

class InputProvider : public Input::InputProvider {
  GLFWwindow *window;
  void (*lastCallback)(GLFWwindow *, int, int, int, int) = nullptr;
  void (*lastCharCallback)(GLFWwindow *, unsigned int) = nullptr;
  void (*lastCursorPosCallback)(GLFWwindow *, double, double) = nullptr;
  void (*lastMouseButtonCallback)(GLFWwindow *, int, int, int) = nullptr;

  std::map<::ENGH::Input::InputKey, bool> keysPressed;

  std::vector<KeyCallback>          keyCallbackList;
  std::vector<CharCallback>         charCallbackList;
  std::vector<CursorMoveCallback>   mouseCallbackList;
  std::vector<CursorScrollCallback> scrollCallbackList;

public:

  InputProvider(GLFWwindow *window = 0);

  ~InputProvider() override;

  bool IsPressed(Input::InputKey key) override;

  bool IsFocused() override;

  void RegisterKeyCallback(KeyCallback func) override;

  void RegisterCharCallback(CharCallback func) override;

  void RegisterCursorCallback(CursorMoveCallback func) override;

  void RegisterScrollCallback(CursorScrollCallback func) override;

  void SetCursorPos(double x, double y) override;

private:

  void keyCallback(GLFWwindow *nativeWindow, int key, int scancode, int action, int mods);

  void charCallback(GLFWwindow *nativeWindow, unsigned int c);

  void mouseCallback(GLFWwindow *nativeWindow, double x, double y);

  void mouseButtonCallback(GLFWwindow *nativeWindow, int button, int action, int mods);

  void scrollCallback(GLFWwindow *nativeWindow, double offsetX, double offsetY);

};

}
