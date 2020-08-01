#pragma once

#include <input/input_events.hpp>

namespace ENGH::Input {

class InputProvider {
public:
  virtual ~InputProvider() {};

  virtual bool isPressed(InputKey key) = 0;
};

}
