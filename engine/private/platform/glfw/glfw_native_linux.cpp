#ifdef __linux__
#include <platform/glfw/glfw_native.h>

#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3native.h>

void *getNativeHandleFromGLFWWindow(GLFWwindow *window) {
  Window nativePointer = glfwGetX11Window(window);
  return reinterpret_cast<void *>(nativePointer);
}

#endif