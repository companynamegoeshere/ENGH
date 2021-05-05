#pragma once

#include <input/input_events.hpp>
#include <utility>

namespace ENGH::Input {

class InputProvider {
public:
  using KeyCallback = std::function<void(::ENGH::Input::InputKey, bool)>;
  using CharCallback = std::function<void(unsigned int)>;
  using CursorMoveCallback = std::function<void(double, double)>;
  using CursorScrollCallback = std::function<void(double, double)>;

  virtual ~InputProvider() {};

  virtual bool IsPressed(InputKey key) = 0;

  virtual bool IsFocused() = 0;

  /**
   * Register a InputKey callback, it receives InputKey events from the keyboard
   * and from the mouse
   */
  virtual void RegisterKeyCallback(KeyCallback) = 0;

  virtual void RegisterCharCallback(CharCallback) = 0;

  virtual void RegisterCursorCallback(CursorMoveCallback) = 0;

  virtual void RegisterScrollCallback(CursorScrollCallback) = 0;

  virtual void SetCursorPos(double x, double y) = 0;
};

}
