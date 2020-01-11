#pragma once

#include <functional>

namespace ENGH::Input {

using ActionCallback = std::function<void(bool pressed, double delta)>;
using AxisCallback = std::function<void(double axis, double delta)>;

enum InputKey {
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

  // TODO More keys

};

}
