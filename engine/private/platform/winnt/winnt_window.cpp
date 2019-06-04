#include <exception>

#include <stdexcept>

#include <platform/winnt/winnt_window.hpp>

namespace ENGH::Platform::WinNT {

    void WinNTWindow::Init() {
        switch (config.renderPreference) {
            case RenderLibrary::NONE:
                break;
            case RenderLibrary::OPENGL: {
                if (!glfwInit()) {
                    ENGH_CORE_FATAL("could not initialize glfw (OpenGL)");
                    throw std::runtime_error("could not initialize glfw (OpenGL)");
                }

                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                nativeWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
                if (!nativeWindow) {
                    throw std::runtime_error("could not create glfw window");
                }
                context = std::make_shared<Render::OpenGL::OpenGLRenderContext>(nativeWindow);
                context->Setup();
            }
                break;
            default:
                ENGH_CORE_FATAL("invalid render configuration");
                break;
        }
    }

    std::shared_ptr<Render::RenderContext> WinNTWindow::getContext() const {
        return std::dynamic_pointer_cast<Render::RenderContext>(context);
    }

    WinNTWindow::~WinNTWindow() {
        glfwDestroyWindow(nativeWindow);
    }

}
