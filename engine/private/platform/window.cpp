#include <platform/window.hpp>
#include <platform/glfw/glfw_window.hpp>

ENGH::Platform::Window::Window(filament::Engine *engine, Config config) :
    engine(engine),
    config(std::move(config)) {};

ENGH::Platform::Window::~Window() {}
