#pragma once

#include <input/input_events.hpp>

namespace ENGH::Input {

class InputProvider {
public:
  virtual bool isPressed(InputKey key) const = 0;

};

}
