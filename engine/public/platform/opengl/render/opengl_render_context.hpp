#pragma once

#include <GLFW/glfw3.h>

#include <platform/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

    class OpenGLRenderContext : RenderContext {
        GLFWwindow* window;
    public:
        explicit OpenGLRenderContext(GLFWwindow* window);

        void Setup() override;

        void SwapBuffers() override;

    };

}
