#pragma once

#include <platform/window.hpp>

#include <backend/DriverEnums.h>

namespace filament {
class Engine;
class Renderer;
class View;
};

namespace ENGH::Platform {

class ECore {
  filament::Engine   *engine = nullptr;
  filament::Renderer *renderer = nullptr;

public:
  ECore();

  ~ECore();

  void Setup(filament::backend::Backend backend = filament::backend::Backend::DEFAULT);

  Window *CreateWindow(Window::Config config);

  inline filament::Renderer &GetRenderer() const { return *renderer; }

  inline filament::Engine *GetEngine() const { return engine; }
};

}
