#pragma once

#include <platform/window.hpp>

struct GLFWwindow;
namespace ENGH::Platform::WinNT {

    class WinNTWindow : Window {
        GLFWwindow *nativeWindow;

    public:
        WinNTWindow(const std::string &title, uint width, uint height, const Config &config);

        void show() override;

        void hide() override;

        Render::RenderContext *getContext() const override;

        virtual ~WinNTWindow();

    };

}