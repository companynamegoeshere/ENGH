#include <platform/window.hpp>
#include <platform/glfw/glfw_window.hpp>
#include <platform/engh.hpp>

ENGH::Platform::Window::Window(ECore *engh, Config config) :
    engh(engh),
    config(std::move(config)) {};

ENGH::Platform::Window::~Window() {}
