#include <glad/gl.h>

#include <platform/opengl/render/opengl_render_context.hpp>

ENGH::Platform::Render::OpenGL::OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *window) :
        window(window) {}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::Setup() {
    glfwMakeContextCurrent(window);
    if(int status = gladLoadGL(glfwGetProcAddress); !status) {
        ENGH_CORE_FATAL("could not initialize glad");
    }
}

void ENGH::Platform::Render::OpenGL::OpenGLRenderContext::SwapBuffers() {
    glfwSwapBuffers(window);
}
