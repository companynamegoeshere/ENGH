#pragma once

#include <input/input_provider.hpp>

struct GLFWwindow;

namespace ENGH::Platform::OpenGL {

class GLFWInputProvider : public Input::InputProvider {
  GLFWwindow *window;

public:
  GLFWInputProvider(GLFWwindow *window = 0);

  bool isPressed(Input::InputKey key) const override;
};

}
