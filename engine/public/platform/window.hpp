#pragma once

#include <string>

#include <core/data_types.hpp>
#include <core/engine.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::Platform {

class Window {
public:
    using RenderCallback = std::function<void(float time)>;
    struct Config {
        std::string           title;
        uint                  width, height;
    };
protected:
    Config config;

public:
  explicit Window(Config  = {});

  virtual ~Window() = 0;

  virtual void Init() = 0;

  virtual void Loop(RenderCallback) = 0;

  virtual std::shared_ptr<Render::RenderContext> GetContext() const = 0;

  static std::shared_ptr<Window> CreateWindow(Window::Config cfg, Render::RenderLibrary library);

};

}