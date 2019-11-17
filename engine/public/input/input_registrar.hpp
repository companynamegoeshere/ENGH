#pragma once

#include <input/input_events.hpp>

namespace ENGH::Input {

class InputHandler;

class InputRegistrar {
  friend InputHandler;
  InputHandler &input;

  InputRegistrar(InputHandler &input);

public:

  void BindAction(const std::string &name, ActionCallback);

  void BindAxis(const std::string &name, AxisCallback);
};

}
