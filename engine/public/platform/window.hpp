#pragma once

#include <string>

#include <core/data_types.hpp>
#include <core/engine.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::Platform {

    class Window {
    public:
        struct Config {
            std::string   title;
            uint          width, height;
            RenderLibrary renderPreference;
        };
    protected:
        Config config;

    public:
        explicit Window(Config  = {});

        virtual void Init() = 0;

        virtual std::shared_ptr<Render::RenderContext> getContext() const = 0;

        virtual ~Window() = 0;

    };

}