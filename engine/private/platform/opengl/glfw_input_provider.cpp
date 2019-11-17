#include <platform/opengl/glfw_input_provider.hpp>
#include <GLFW/glfw3.h>
#include <map>

namespace ENGH::Platform::OpenGL {

using namespace Input;

static std::map<Input::InputKey, int> keyMapping = {
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
};

GLFWInputProvider::GLFWInputProvider(GLFWwindow *window) : window(window) {}

bool ENGH::Platform::OpenGL::GLFWInputProvider::isPressed(ENGH::Input::InputKey key) const {
  return glfwGetKey(window, keyMapping[key]) == GLFW_PRESS;
}

}
