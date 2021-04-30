#include <platform/glfw/glfw_window.hpp>
#include <platform/engh.hpp>

//#include <glad/gl.h>
#include <GLFW/glfw3.h>

#if _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#elif __linux__
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif
#include <GLFW/glfw3native.h>

#include <filament/Engine.h>
#include <filament/Renderer.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <utility>

#include <iostream>

namespace ENGH::Platform::GLFW {

Window::~Window() {
  glfwDestroyWindow(glfwWindow);
}

Window::Window(ECore *engh, Config config) :
    ::ENGH::Platform::Window(engh, std::move(config)),
    frameTime(0.0),
    initialized(false),
    inputProvider() {}

void Window::Init() {
  if (initialized) {
    ENGH_CORE_THROW_FATAL("window already initialized");
  }
  initialized = true;
  if (!glfwInit()) {
    const char *desc;
    glfwGetError(&desc);
    ENGH_CORE_THROW_FATAL("could not initialize GLFW: ", desc);
  }

//  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//  glfwWindowHint(GLFW_DECORATED, GL_FALSE);

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  width      = config.width;
  height     = config.height;
  glfwWindow = glfwCreateWindow(width, height, config.title.c_str(), nullptr, nullptr);
  if (!glfwWindow) {
    const char *desc;
    glfwGetError(&desc);
    ENGH_CORE_THROW_FATAL("could not create glfw window: ", desc);
  }
  inputProvider = InputProvider(glfwWindow);
  auto userPointer = new UserData{*this, inputProvider};
  glfwSetWindowUserPointer(glfwWindow, userPointer);

  glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow *glfwWindow, int width, int height) {
    auto &w = reinterpret_cast<UserData *>(glfwGetWindowUserPointer(glfwWindow))->window;
    w.doResize(width, height);
  });

  swapChain = engh->GetEngine()->createSwapChain(GetNativeHandler());
}

void Window::StartLoop() {

  if (!renderCallback) {
    ENGH_CORE_ERROR("Could not start Loop, Render callback is not set");
    return;
  }

  filament::Renderer &renderer = engh->GetRenderer();

  using namespace std::chrono_literals;
  using clock = std::chrono::high_resolution_clock;
  using secD = std::chrono::duration<double, std::chrono::seconds>;

  constexpr std::chrono::nanoseconds desireFrameTime = std::chrono::nanoseconds((int)1e9) / 60; // 60 FPS

  auto begin = clock::now();
  auto last = begin;
  while (IsOpen()) {
    if (nextView != nullptr) {
      currentView = nextView;
      nextView    = nullptr;
    }

    auto now           = clock::now();
    auto cFrameTime    = now - last;
    auto nanoNow       = std::chrono::duration_cast<std::chrono::nanoseconds>(now - begin).count();
    auto nanoFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(cFrameTime).count();
    frameTime = nanoFrameTime / (double) 1e9;
    last      = now;

    this->renderCallback(frameTime, nanoNow / 1e9);

#if UTILS_HAS_THREADING == 0
    engine->execute();
#endif

    static int skippingFrames = 0;
    static int frames = 0;
    if (renderer.beginFrame(GetSwapChain(), nanoNow)) {
      renderer.render(currentView);
      renderer.endFrame();
      frames++;
    } else {
      skippingFrames++;
    }
    glfwPollEvents();

    static long long nextNano = 0;
    if(nanoNow > nextNano) {
      nextNano = nanoNow + (int)1e9;
      std::cout << "Skipped frames: " << skippingFrames << " FPS: " << frames << " NOW: " << nanoNow * 1e-9 << " NEXT: " << nextNano * 1e-9 << std::endl;
      frames = 0;
      skippingFrames = 0;
    }

    if (cFrameTime < desireFrameTime) {
      std::this_thread::sleep_for(desireFrameTime - cFrameTime);
    }
  }

  engh->GetEngine()->destroy(swapChain);
}

std::pair<double, double> Window::GetSize() {
  return std::make_pair(static_cast<double>(width), static_cast<double>(height));
}

double Window::GetFrameTime() {
  return frameTime;
}

double Window::GetTotalTime() {
  return totalTime;
}

Input::InputProvider *Window::GetInputProvider() {
  return &inputProvider;
}

bool Window::IsOpen() {
  return glfwWindowShouldClose(glfwWindow) == 0;
}

void *Window::GetNativeHandler() {
#ifdef _WIN32
  HWND nativePointer = glfwGetWin32Window(glfwWindow);
#else
#error Only windows supported
#endif
  return reinterpret_cast<void *>(nativePointer);
}

void Window::doResize(int width, int height) {
  this->width  = width;
  this->height = height;
}

}
