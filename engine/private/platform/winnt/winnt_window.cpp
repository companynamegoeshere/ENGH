#include <exception>

#include <stdexcept>

#include <platform/winnt/winnt_window.hpp>

namespace ENGH::Platform::WinNT {

WinNTWindow::~WinNTWindow() {
    glfwDestroyWindow(nativeWindow);
}

WinNTWindow::WinNTWindow(Window::Config config) : Window(config), initialized(false) {}

void WinNTWindow::Init() {
    if (initialized) {
        ENGH_CORE_THROW_FATAL("window already initialized");
    }
    initialized = true;
    switch (config.renderPreference) {
        case Render::RenderLibrary::NONE:break;
        case Render::RenderLibrary::OPENGL: {
            if (!glfwInit()) {
                const char *desc;
                glfwGetError(&desc);
                ENGH_CORE_THROW_FATAL("could not initialize glfw (OpenGL): ", desc);
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#ifdef ENGH_DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

            nativeWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
            if (!nativeWindow) {
                const char *desc;
                glfwGetError(&desc);
                ENGH_CORE_THROW_FATAL("could not create glfw window: ", desc);
            }
            context = std::make_shared<Render::OpenGL::OpenGLRenderContext>(nativeWindow);
            context->Setup();

            glDebugMessageCallback(
                [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg,
                   const void *data) {
                    ENGH_CORE_FINER(msg);
                }, nullptr);

            glfwSetFramebufferSizeCallback(nativeWindow, [](GLFWwindow *, int width, int height) {
                glViewport(0, 0, width, height);
            });

            glfwSwapInterval(1);
        }
            break;
        default: {
            ENGH_CORE_THROW_FATAL("invalid render configuration");
        }
            break;
    }
}

void WinNTWindow::Loop(RenderCallback callback) {
    while (!glfwWindowShouldClose(nativeWindow)) {
        callback(glfwGetTime());
        glfwPollEvents();
    }
}

std::shared_ptr<Render::RenderContext> WinNTWindow::GetContext() const {
    return std::dynamic_pointer_cast<Render::RenderContext>(context);
}

}
