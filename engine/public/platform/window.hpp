#pragma once

#include <string>

#include <core/data_types.hpp>
#include <core/engine.hpp>
#include <input/input_provider.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::Platform {

class Window {
public:
  using RenderCallback = std::function<void(double delta, double time)>;
  using ResizeCallback = std::function<void(double width, double height)>;

  struct Config {
    std::string title;
    uint width, height;
  };
protected:
  Config config;

  ResizeCallback resizeCallback;

public:
  explicit Window(Config  = {});

  virtual ~Window() = 0;

  virtual void Init() = 0;

  virtual void Loop(RenderCallback) = 0;

  virtual std::pair<double, double> GetSize() = 0;

  virtual const Input::InputProvider *GetInputProvider() const = 0;

  virtual std::shared_ptr<Render::RenderContext> GetContext() const = 0;

  virtual void SetResizeCallback(ResizeCallback);

  static std::shared_ptr<Window> CreateWindow(Window::Config cfg, Render::RenderLibrary library);

};

}