#include <platform/engh.hpp>

#include <platform/glfw/glfw_window.hpp>
#include <filament/Engine.h>

namespace ENGH::Platform {

ENGH::ENGH(filament::backend::Backend backend) {
  engine = filament::Engine::create(backend);
}
Window *ENGH::CreateWindow(Window::Config config) {
  return reinterpret_cast<::ENGH::Platform::Window*>(new GLFW::Window(engine, config));
}

}
