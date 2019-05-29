#include <platform/window.hpp>
#include <utility>

ENGH::Platform::Window::Window(std::string title, uint width, uint height, const Config&) :
        title(std::move(title)), width(width), height(height) {}