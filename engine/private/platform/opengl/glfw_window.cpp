#include <platform/opengl/glfw_window.hpp>

#include <chrono>
#include <thread>
#include <atomic>
#include <utility>

namespace ENGH::Platform::OpenGL {

GLFWWindow::~GLFWWindow() {
  glfwDestroyWindow(nativeWindow);
}

GLFWWindow::GLFWWindow(Window::Config config) :
    Window(std::move(config)),
    frameTime(0.0),
    initialized(false),
    inputProvider() {}

void GLFWWindow::Init() {
  if (initialized) {
    ENGH_CORE_THROW_FATAL("window already initialized");
  }
  initialized = true;
  if (!glfwInit()) {
    const char *desc;
    glfwGetError(&desc);
    ENGH_CORE_THROW_FATAL("could not initialize glfw (OpenGL): ", desc);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#ifdef ENGH_DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

  nativeWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
  if (!nativeWindow) {
    const char *desc;
    glfwGetError(&desc);
    ENGH_CORE_THROW_FATAL("could not create glfw window: ", desc);
  }
  inputProvider = GLFWInputProvider(nativeWindow);
  auto userPointer = new UserData { this, &inputProvider };
  glfwSetWindowUserPointer(nativeWindow, userPointer);
  context = std::make_shared<Render::OpenGL::OpenGLRenderContext>(nativeWindow);
  context->Setup();

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
  glDebugMessageCallback(
      [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg,
         const void *data) {
        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:ENGH_CORE_ERROR(msg);
          break;
        case GL_DEBUG_SEVERITY_MEDIUM:ENGH_CORE_WARN(msg);
          break;
        case GL_DEBUG_SEVERITY_LOW:ENGH_CORE_FINER(msg);
          break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:ENGH_CORE_FINEST(msg);
          break;
        }
      }, nullptr);

  auto doResize = [](GLFWwindow *glfwWindow, int width, int height) {
    GLFWWindow *window = reinterpret_cast<UserData *>(glfwGetWindowUserPointer(glfwWindow))->window;
    auto fb = std::dynamic_pointer_cast<Render::OpenGL::OpenGLRenderContext>(window->context)->GetScreenFrameBuffer();
    std::dynamic_pointer_cast<Render::OpenGL::OpenGLFrameBuffer>(fb)->Resize(width, height);
    window->resizeCallback(width, height);
  };
  glfwSetFramebufferSizeCallback(nativeWindow, doResize);

  int width, height;
  glfwGetFramebufferSize(nativeWindow, &width, &height);
  glViewport(0, 0, width, height);

  glfwSwapInterval(1);
}

void GLFWWindow::StartLoop() {

  if (!renderCallback) {
    ENGH_CORE_ERROR("Could not start Loop, Render callback is not set");
    return;
  }

  if (!setupRenderCallback) {
    ENGH_CORE_ERROR("Could not start Loop, Setup Render callback is not set");
    return;
  }

  if (!updateCallback) {
    ENGH_CORE_ERROR("Could not start Loop, Update callback is not set");
    return;
  }

  std::atomic<bool> renderLock = false;
  auto wait = [&renderLock]() { while (renderLock); };

  const double desiredTickCount = 1.0 / 240;

  bool run = true;

  auto updateThread = std::thread([&]() {
    std::chrono::time_point lastTime = std::chrono::steady_clock::now();
    int lastSec = 5, tickCount = 0;
    double delay = 0, total = 0;

    while (run) {
      auto now = std::chrono::steady_clock::now();
      double delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTime).count() * 1e-9;
      total += delta;
      lastTime = now;

      delay += desiredTickCount - delta;
      if (delay > 0)
        std::this_thread::sleep_for(std::chrono::duration<double>(delay));

      tickCount++;
      if (total > lastSec) {
        lastSec += 5;
        ENGH_CORE_FINER("World tick count: ", tickCount / 5, " delay: ", delay);
        tickCount = 0;
      }

      if (!renderLock) {
        renderLock = true;
        this->updateCallback(delta, total);
        renderLock = false;
      }
    }
  });

  double last = glfwGetTime();

  while (IsOpen()) {
    double now = glfwGetTime();
    frameTime = now - last;
    last = now;

    this->renderCallback();
    glfwPollEvents();
    wait();
    renderLock = true;
    setupRenderCallback();
    renderLock = false;
  }
  run = false;
  updateThread.join();
}

std::pair<double, double> GLFWWindow::GetSize() {
  int w, h;
  glfwGetFramebufferSize(nativeWindow, &w, &h);
  return std::make_pair(static_cast<double>(w), static_cast<double>(h));
}

double GLFWWindow::GetFrameTime() {
  return frameTime;
}

std::shared_ptr<Render::RenderContext> GLFWWindow::GetContext() {
  return std::dynamic_pointer_cast<Render::RenderContext>(context);
}

Input::InputProvider *GLFWWindow::GetInputProvider() {
  return &inputProvider;
}
bool GLFWWindow::IsOpen() {
  return glfwWindowShouldClose(nativeWindow) == 0;
}

}
