#include <platform/winnt/winnt_window.hpp>

#include <exception>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace ENGH::Platform::WinNT {


    WinNTWindow::WinNTWindow(const std::string &title, uint width, uint height, const Config &config)
            : Window(title, width, height, config) {

        switch (config.renderPreference) {
            case RenderLibrary::NONE:
                break;
            case RenderLibrary::OPENGL: {
                if (!glfwInit()) {
                    ENGH_CORE_ERROR("could not initialize glfw (OpenGL)");
                    throw std::runtime_error("could not initialize glfw (OpenGL)");
                }

                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                nativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
                if (!nativeWindow) {
                    throw std::runtime_error("could not create glfw window");
                }
            }
                break;
        }

    }


    void WinNTWindow::show() {

    }

    void WinNTWindow::hide() {

    }

    Render::RenderContext *WinNTWindow::getContext() const {
        return nullptr;
    }


    WinNTWindow::~WinNTWindow() {
        glfwDestroyWindow(nativeWindow);
    }

}