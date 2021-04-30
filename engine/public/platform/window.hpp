#pragma once

#include <string>

#include <core/data_types.hpp>
#include <core/engine.hpp>
#include <input/input_provider.hpp>

namespace filament {
class Engine;
class SwapChain;
class View;
}

namespace ENGH::Platform {
class ECore;

class Window {
public:
  using RenderCallback = std::function<void(double delta, double time)>;
  using ResizeCallback = std::function<void(double width, double height)>;

  struct Config {
    bool resizable;
    std::string title;
    uint width, height;

  };
protected:
  ECore *engh;
  filament::SwapChain *swapChain;

  filament::View *currentView;
  filament::View *nextView;
  Config config;

public:

  RenderCallback renderCallback;
  ResizeCallback resizeCallback = [](double w, double h) {};

  explicit Window(ECore *engh, Config  = {});

  virtual ~Window() = 0;

  virtual void Init() = 0;

  virtual void StartLoop() = 0;

  virtual bool IsOpen() = 0;

  virtual std::pair<double, double> GetSize() = 0;

  virtual double GetFrameTime() = 0;

  virtual double GetTotalTime() = 0;

  virtual Input::InputProvider *GetInputProvider() = 0;

  inline filament::SwapChain *GetSwapChain() { return swapChain; }

  void SelectView(filament::View *next) { nextView = next; }

  virtual void* GetNativeHandler() = 0;
};

}