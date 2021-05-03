#include <platform/glfw/glfw_input_provider.hpp>
#include <platform/glfw/glfw_window.hpp>
#include <GLFW/glfw3.h>
#include <map>

namespace ENGH::Platform::GLFW {

using namespace Input;

static const std::map<Input::InputKey, int> keyMapping        = {

    {MOUSE_LEFT, GLFW_MOUSE_BUTTON_LEFT},
    {MOUSE_RIGHT, GLFW_MOUSE_BUTTON_RIGHT},
    {MOUSE_MIDDLE, GLFW_MOUSE_BUTTON_MIDDLE},
    {MOUSE_BTN_4, GLFW_MOUSE_BUTTON_4},
    {MOUSE_BTN_5, GLFW_MOUSE_BUTTON_5},

    {KEY_1, GLFW_KEY_1},
    {KEY_2, GLFW_KEY_2},
    {KEY_3, GLFW_KEY_3},
    {KEY_4, GLFW_KEY_4},
    {KEY_5, GLFW_KEY_5},
    {KEY_6, GLFW_KEY_6},
    {KEY_7, GLFW_KEY_7},
    {KEY_8, GLFW_KEY_8},
    {KEY_9, GLFW_KEY_9},
    {KEY_0, GLFW_KEY_0},

    {KEY_NP_1, GLFW_KEY_KP_1},
    {KEY_NP_2, GLFW_KEY_KP_2},
    {KEY_NP_3, GLFW_KEY_KP_3},
    {KEY_NP_4, GLFW_KEY_KP_4},
    {KEY_NP_5, GLFW_KEY_KP_5},
    {KEY_NP_6, GLFW_KEY_KP_6},
    {KEY_NP_7, GLFW_KEY_KP_7},
    {KEY_NP_8, GLFW_KEY_KP_8},
    {KEY_NP_9, GLFW_KEY_KP_9},
    {KEY_NP_0, GLFW_KEY_KP_0},
    {KEY_NP_ENTER, GLFW_KEY_KP_ENTER},

    {KEY_TAB, GLFW_KEY_TAB},
    {KEY_SPACE, GLFW_KEY_SPACE},
    {KEY_BACKSPACE, GLFW_KEY_BACKSPACE},
    {KEY_ENTER, GLFW_KEY_ENTER},

    {KEY_RIGHT, GLFW_KEY_RIGHT},
    {KEY_LEFT, GLFW_KEY_LEFT},
    {KEY_UP, GLFW_KEY_UP},
    {KEY_DOWN, GLFW_KEY_DOWN},

    {KEY_L_CTRL, GLFW_KEY_LEFT_CONTROL},
    {KEY_R_CTRL, GLFW_KEY_RIGHT_CONTROL},
    {KEY_L_SHIFT, GLFW_KEY_LEFT_SHIFT},
    {KEY_R_SHIFT, GLFW_KEY_RIGHT_SHIFT},
    {KEY_L_ALT, GLFW_KEY_LEFT_ALT},
    {KEY_R_ALT, GLFW_KEY_RIGHT_ALT},

    {KEY_A, GLFW_KEY_A},
    {KEY_B, GLFW_KEY_B},
    {KEY_C, GLFW_KEY_C},
    {KEY_D, GLFW_KEY_D},
    {KEY_E, GLFW_KEY_E},
    {KEY_F, GLFW_KEY_F},
    {KEY_G, GLFW_KEY_G},
    {KEY_H, GLFW_KEY_H},
    {KEY_I, GLFW_KEY_I},
    {KEY_J, GLFW_KEY_J},
    {KEY_K, GLFW_KEY_K},
    {KEY_L, GLFW_KEY_L},
    {KEY_M, GLFW_KEY_M},
    {KEY_N, GLFW_KEY_N},
    {KEY_O, GLFW_KEY_O},
    {KEY_P, GLFW_KEY_P},
    {KEY_Q, GLFW_KEY_Q},
    {KEY_R, GLFW_KEY_R},
    {KEY_S, GLFW_KEY_S},
    {KEY_T, GLFW_KEY_T},
    {KEY_U, GLFW_KEY_U},
    {KEY_V, GLFW_KEY_V},
    {KEY_W, GLFW_KEY_W},
    {KEY_X, GLFW_KEY_X},
    {KEY_Y, GLFW_KEY_Y},
    {KEY_Z, GLFW_KEY_Z},

    {KEY_ESC, GLFW_KEY_ESCAPE},

    {KEY_INSERT, GLFW_KEY_INSERT},
    {KEY_DELETE, GLFW_KEY_DELETE},
    {KEY_HOME, GLFW_KEY_HOME},
    {KEY_END, GLFW_KEY_END},
    {KEY_PG_UP, GLFW_KEY_PAGE_UP},
    {KEY_PG_DOWN, GLFW_KEY_PAGE_DOWN},
};

static std::map<int, Input::InputKey> _reverse(const std::map<Input::InputKey, int> &m) {
  std::map<int, Input::InputKey> r;
  for (const auto[p1, p2] : m) {
    r[p2] = p1;
  }
  return r;
}
static const std::map<int, Input::InputKey> reverseKeyMapping = _reverse(keyMapping);

static inline InputProvider* getProvider(GLFWwindow *window) {
  static std::pair<GLFWwindow *, InputProvider*> last;
  if (last.first != window) {
    last.first  = window;
    last.second = &reinterpret_cast<GLFW::Window::UserData *>(glfwGetWindowUserPointer(window))->inputProvider;
  }
  return last.second;
}

InputProvider::InputProvider(GLFWwindow *window) : window(window) {
  if(window != nullptr) {
    lastCallback = glfwSetKeyCallback(window, [](auto *w, int key, int scancode, int action, int mods) {
      getProvider(w)->keyCallback(w, key, scancode, action, mods);
    });
    lastCharCallback = glfwSetCharCallback(window, [](auto *w, unsigned int c) {
      getProvider(w)->charCallback(w, c);
    });
    lastCursorPosCallback = glfwSetCursorPosCallback(window, [](auto *w, double x, double y) {
      getProvider(w)->mouseCallback(w, x, y);
    });
    lastMouseButtonCallback = glfwSetMouseButtonCallback(window, [](auto *w, int button, int action, int mods) {
      getProvider(w)->mouseButtonCallback(w, button, action, mods);
    });
  }
}

InputProvider::~InputProvider() {
  if(window != nullptr && lastCallback != nullptr) {
    glfwSetKeyCallback(window, lastCallback);
    glfwSetCharCallback(window, lastCharCallback);
  }
}

bool InputProvider::IsPressed(::ENGH::Input::InputKey key) {
  return keysPressed[key];
}

bool InputProvider::IsFocused() {
  return glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;
}

void InputProvider::RegisterKeyCallback(InputProvider::KeyCallback func) {
  keyCallbackList.push_back(func);
}

void InputProvider::RegisterCharCallback(InputProvider::CharCallback func) {
  charCallbackList.push_back(func);
}

void InputProvider::RegisterCursorCallback(InputProvider::CursorMoveCallback func) {
  mouseCallbackList.push_back(func);
}

void InputProvider::SetCursorPos(double x, double y) {
  glfwSetCursorPos(window, x, y);
};

void InputProvider::keyCallback(GLFWwindow *nativeWindow, int key, int scancode, int action, int mods) {
  const auto pressed = action == GLFW_PRESS;
  if (pressed || action == GLFW_RELEASE) {
    auto e = reverseKeyMapping.find(key);
    if(e != reverseKeyMapping.end()) {
      keysPressed[e->second] = pressed;
      for (const auto &item : keyCallbackList) {
        item(e->second, pressed);
      }
    }
  }
  if(lastCallback != nullptr) {
    lastCallback(nativeWindow, key, scancode, action, mods);
  }
}

void InputProvider::charCallback(GLFWwindow *nativeWindow, unsigned int c) {
  for (const auto &item : charCallbackList) {
    item(c);
  }
  if(lastCharCallback != nullptr) {
    lastCharCallback(nativeWindow, c);
  }
}

void InputProvider::mouseCallback(GLFWwindow *nativeWindow, double x, double y) {
  for (const auto &item : mouseCallbackList) {
    item(x, y);
  }
  if(lastCursorPosCallback != nullptr) {
    lastCursorPosCallback(nativeWindow, x, y);
  }
}

void InputProvider::mouseButtonCallback(GLFWwindow *nativeWindow, int button, int action, int mods) {
  const auto pressed = action == GLFW_PRESS;
  if (pressed || action == GLFW_RELEASE) {
    auto e = reverseKeyMapping.find(button);
    if(e != reverseKeyMapping.end()) {
      keysPressed[e->second] = pressed;
      for (const auto &item : keyCallbackList) {
        item(e->second, pressed);
      }
    }
  }
  if(lastMouseButtonCallback != nullptr) {
    lastMouseButtonCallback(nativeWindow, button, action, mods);
  }
}

}
