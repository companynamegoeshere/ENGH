#pragma once

#include <string>

#include <core/data_types.hpp>
#include <core/engine.hpp>
#include <input/input_provider.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::Platform {

class Window {
public:
  using UpdateCallback = std::function<void(double delta, double time)>;
  using RenderCallback = std::function<void()>;
  using ResizeCallback = std::function<void(double width, double height)>;

  struct Config {
    std::string title;
    uint width, height;
  };
protected:
  Config config;

  UpdateCallback updateCallback;
  RenderCallback setupRenderCallback;
  RenderCallback renderCallback;
  ResizeCallback resizeCallback;

public:

  explicit Window(Config  = {});

  virtual ~Window() = 0;

  virtual void Init() = 0;

  virtual void StartLoop() = 0;

  virtual bool IsOpen() = 0;

  virtual std::pair<double, double> GetSize() = 0;

  virtual const Input::InputProvider *GetInputProvider() const = 0;

  virtual std::shared_ptr<Render::RenderContext> GetContext() const = 0;

  virtual void SetUpdateCallback(UpdateCallback);

  virtual void SetSetupRenderCallback(RenderCallback);

  virtual void SetRenderCallback(RenderCallback);

  virtual void SetResizeCallback(ResizeCallback);

  static std::shared_ptr<Window> CreateWindow(Window::Config cfg, Render::RenderLibrary library);

};

}