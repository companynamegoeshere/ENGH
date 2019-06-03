#pragma once

#include <platform/render/render_context.hpp>

namespace ENGH::Platform::Render::OpenGL {

    class OpenGLRenderContext : RenderContext {
    public:

        void Setup() override;

        void SwapBuffers() override;

    };

}
