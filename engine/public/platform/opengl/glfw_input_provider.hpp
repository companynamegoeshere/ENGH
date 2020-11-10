#pragma once

#include <input/input_provider.hpp>

#include <map>

struct GLFWwindow;

namespace ENGH::Platform::OpenGL {

class GLFWInputProvider : public Input::InputProvider {
  GLFWwindow *window;
  void (*lastCallback)(GLFWwindow *, int, int, int, int);

  std::map<ENGH::Input::InputKey, bool> keysPressed;

  static void funcCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  void callback(GLFWwindow *nativeWindow, int key, int scancode, int action, int mods);

public:
  GLFWInputProvider(GLFWwindow *window = 0);

  ~GLFWInputProvider() override;

  bool isPressed(Input::InputKey key) override;
};

}
