#pragma once

namespace ENGH::Platform::Render {

    class RenderContext {
    public:

        virtual void Setup() = 0;

        virtual void SwapBuffers() = 0;

    };

}
