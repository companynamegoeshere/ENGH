#include <platform/engh.hpp>

#include <platform/glfw/glfw_window.hpp>
#include <filament/Engine.h>

namespace ENGH::Platform {

ECore::ECore() {}

ECore::~ECore() {
  if(engine != nullptr) {
    if(renderer != nullptr) {
      engine->destroy(renderer);
      renderer = nullptr;
    }
    filament::Engine::destroy(engine);
    engine = nullptr;
  }
};

void ECore::Setup(filament::backend::Backend backend) {
  engine = filament::Engine::create(backend);
  renderer = engine->createRenderer();
}

Window *ECore::CreateWindow(Window::Config config) {
  return reinterpret_cast<::ENGH::Platform::Window*>(new GLFW::Window(this, config));
}

}
