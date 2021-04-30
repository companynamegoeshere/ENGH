#ifdef _WIN32
#include <platform/glfw/glfw_native.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>

void *getNativeHandleFromGLFWWindow(GLFWwindow *window) {
  HWND nativePointer = glfwGetWin32Window(window);
  return reinterpret_cast<void *>(nativePointer);
}

#endif