#pragma once

#include <platform/render/render_context.hpp>

#include <core/data_types.hpp>
#include <string>

namespace ENGH::Platform {

    class Window {
    public:
        struct Config {
            std::string render_preference;
        };
    protected:

        std::string title;
        uint        width;
        uint        height;

    public:
        Window(std::string title, uint width, uint height, const Config& = {});

        virtual void show() = 0;

        virtual void hide() = 0;

        virtual Render::RenderContext *getContext() const = 0;

    };

}