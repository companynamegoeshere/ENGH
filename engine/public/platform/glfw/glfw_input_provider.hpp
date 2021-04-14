#pragma once

#include <input/input_provider.hpp>

#include <map>

struct GLFWwindow;

namespace ENGH::Platform::GLFW {

class InputProvider : public Input::InputProvider {
  GLFWwindow *window;
  void (*lastCallback)(GLFWwindow *, int, int, int, int);

  std::map<::ENGH::Input::InputKey, bool> keysPressed;

  static void funcCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  void callback(GLFWwindow *nativeWindow, int key, int scancode, int action, int mods);

public:
  InputProvider(GLFWwindow *window = 0);

  ~InputProvider() override;

  bool isPressed(Input::InputKey key) override;
};

}
