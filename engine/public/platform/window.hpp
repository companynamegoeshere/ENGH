#pragma once

#include <string>

#include <core/data_types.hpp>
#include <core/engine.hpp>
#include <input/input_provider.hpp>

namespace filament {
class Engine;
}

namespace ENGH::Platform {

class Window {
public:
  using UpdateCallback = std::function<void(double delta, double time)>;
  using RenderCallback = std::function<void()>;
  using ResizeCallback = std::function<void(double width, double height)>;

  struct Config {
    bool resizable;
    std::string title;
    uint width, height;

  };
protected:
  filament::Engine *engine;
  Config config;

public:

  UpdateCallback updateCallback;
  RenderCallback renderCallback;
  RenderCallback setupRenderCallback = []() {};
  ResizeCallback resizeCallback = [](double w, double h) {};

  explicit Window(filament::Engine* engine, Config  = {});

  virtual ~Window() = 0;

  virtual void Init() = 0;

  virtual void StartLoop() = 0;

  virtual bool IsOpen() = 0;

  virtual std::pair<double, double> GetSize() = 0;

  virtual double GetFrameTime() = 0;

  virtual double GetTotalTime() = 0;

  virtual Input::InputProvider *GetInputProvider() = 0;

//  virtual std::shared_ptr<Render::RenderContext> GetContext() = 0;

  virtual void* GetNativeHandler() = 0;
};

}