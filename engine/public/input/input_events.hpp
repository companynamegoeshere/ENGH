#pragma once

#include <core/debug.hpp>
#include <functional>

namespace ENGH::Input {

using ActionCallback = std::function<void(bool pressed, double delta)>;
using AxisCallback = std::function<void(double axis, double delta)>;

enum InputKey {

  MOUSE_LEFT,
  MOUSE_RIGHT,
  MOUSE_MIDDLE,
  MOUSE_BTN_4,
  MOUSE_BTN_5,

  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_0,

  KEY_NP_1,
  KEY_NP_2,
  KEY_NP_3,
  KEY_NP_4,
  KEY_NP_5,
  KEY_NP_6,
  KEY_NP_7,
  KEY_NP_8,
  KEY_NP_9,
  KEY_NP_0,
  KEY_NP_ENTER,

  KEY_TAB,
  KEY_SPACE,
  KEY_BACKSPACE,
  KEY_ENTER,

  KEY_RIGHT,
  KEY_LEFT,
  KEY_UP,
  KEY_DOWN,

  KEY_L_CTRL,
  KEY_R_CTRL,
  KEY_L_SHIFT,
  KEY_R_SHIFT,
  KEY_L_ALT,
  KEY_R_ALT,

  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,

  KEY_ESC,

  KEY_INSERT,
  KEY_DELETE,
  KEY_HOME,
  KEY_END,
  KEY_PG_UP,
  KEY_PG_DOWN,

  // TODO More keys

};

enum KeyType {
  MOUSE,
  KEYBOARD
};

constexpr InputKey MOUSE_BUTTONS[5] = {
    InputKey::MOUSE_LEFT,
    InputKey::MOUSE_RIGHT,
    InputKey::MOUSE_MIDDLE,
    InputKey::MOUSE_BTN_4,
    InputKey::MOUSE_BTN_5
};

static inline KeyType GetKeyType(InputKey key) {
  if (InputKey::MOUSE_LEFT <= key && key <= InputKey::MOUSE_BTN_5) {
    return KeyType::MOUSE;
  }
  if(InputKey::KEY_1 <= key && key <= InputKey::KEY_PG_DOWN) {
    return KeyType::KEYBOARD;
  }
  ASSERT("Invalid InputKey");
  return (KeyType) -1;
}

static inline int GetMouseButton(InputKey key) {
  ASSERT(InputKey::MOUSE_LEFT <= key && key <= InputKey::MOUSE_BTN_5, "InputKey is not a mouse button");
  return key - Input::MOUSE_LEFT;
}

}
