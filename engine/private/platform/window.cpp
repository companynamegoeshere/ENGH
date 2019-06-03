#include <platform/window.hpp>

ENGH::Platform::Window::Window(Config config) :
        config(std::move(config)) {}
