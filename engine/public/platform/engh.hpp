#pragma once

#include <platform/window.hpp>

#include <backend/DriverEnums.h>

namespace filament {
class Engine;
};

namespace ENGH::Platform {

class ENGH {
  filament::Engine *engine;
public:
  ENGH(filament::backend::Backend backend = filament::backend::Backend::DEFAULT);

  Window* CreateWindow(Window::Config config);
};

}
