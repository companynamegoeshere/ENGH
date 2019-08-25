#pragma once

#include <platform/opengl/render/render_context.hpp>
#include <platform/window.hpp>

struct GLFWwindow;
namespace ENGH::Platform::WinNT {

class WinNTWindow : public Window {public:
    bool initialized;

    GLFWwindow *nativeWindow{};

    std::shared_ptr<Render::OpenGL::OpenGLRenderContext> context;

public:

    explicit WinNTWindow(Config config);

    ~WinNTWindow() override;

    void Init() override;

    void Loop(RenderCallback) override;

    std::shared_ptr<Render::RenderContext> GetContext() const override;

};

}