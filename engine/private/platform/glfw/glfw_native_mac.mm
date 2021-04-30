#ifdef __APPLE__
#include <platform/glfw/glfw_native.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

void *getNativeHandleFromGLFWWindow(GLFWwindow *window) {
  NSWindow *win = glfwGetCocoaWindow(window);
  NSView* view = [win contentView];
  return reinterpret_cast<void *>(view);
}

#endif