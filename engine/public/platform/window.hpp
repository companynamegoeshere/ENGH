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
            Render::RenderLibrary renderPreference;
        };
    protected:
        Config config;

    public:
        explicit Window(Config  = {});

        virtual ~Window() = 0;

        virtual void Init() = 0;

        virtual std::shared_ptr<Render::RenderContext> GetContext() const = 0;

    };

}