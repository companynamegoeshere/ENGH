#include <platform/window.hpp>
#include <platform/opengl/glfw_window.hpp>

ENGH::Platform::Window::Window(Config config) :
    config(std::move(config)),
    resizeCallback([](double w, double h) {}) {}

ENGH::Platform::Window::~Window() {}

void ENGH::Platform::Window::SetUpdateCallback(UpdateCallback callback) {
  this->updateCallback = callback;
}

void ENGH::Platform::Window::SetRenderCallback(RenderCallback callback) {
  this->renderCallback = callback;
}

void ENGH::Platform::Window::SetSetupRenderCallback(RenderCallback callback) {
  this->setupRenderCallback = callback;
}

void ENGH::Platform::Window::SetResizeCallback(ResizeCallback callback) {
  this->resizeCallback = callback;
  auto[width, height] = GetSize();
  resizeCallback(width, height);
}

std::shared_ptr<ENGH::Platform::Window> ENGH::Platform::Window::CreateNewWindow(ENGH::Platform::Window::Config cfg,
                                                                                ENGH::Platform::Render::RenderLibrary library) {
  switch (library) {
  case Render::RenderLibrary::NONE:break; // TODO Create headless window
  case Render::RenderLibrary::OPENGL:return std::make_shared<OpenGL::GLFWWindow>(cfg);
  }
  ENGH_CORE_THROW_FATAL("Invalid render library");
  return nullptr;
}
