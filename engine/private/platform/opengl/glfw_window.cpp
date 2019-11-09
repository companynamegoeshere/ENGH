#include <platform/opengl/glfw_window.hpp>
#include <stdexcept>

namespace ENGH::Platform::OpenGL {

GLFWWindow::~GLFWWindow() {
    glfwDestroyWindow(nativeWindow);
}

GLFWWindow::GLFWWindow(Window::Config config) : Window(config), initialized(false) {}

void GLFWWindow::Init() {
    if (initialized) {
        ENGH_CORE_THROW_FATAL("window already initialized");
    }
    initialized = true;
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

    int width, height;
    glfwGetFramebufferSize(nativeWindow, &width, &height);
    glViewport(0, 0, width, height);

    glfwSwapInterval(1);
}

void GLFWWindow::Loop(RenderCallback callback) {
    while (!glfwWindowShouldClose(nativeWindow)) {
        callback(glfwGetTime());
        glfwPollEvents();
    }
}

std::shared_ptr<Render::RenderContext> GLFWWindow::GetContext() const {
    return std::dynamic_pointer_cast<Render::RenderContext>(context);
}

}
