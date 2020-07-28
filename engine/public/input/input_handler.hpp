#pragma once

#include <core/engine.hpp>
#include <input/input_registrar.hpp>
#include <input/input_events.hpp>
#include <input/input_provider.hpp>
#include <string>
#include <map>

namespace ENGH::Input {
class InputRegistrar;

using AxisValue = double;

class InputHandler {
  friend InputRegistrar;
protected:

  TArray<std::pair<InputKey, std::string>> actions;
  TArray<std::tuple<InputKey, std::string, AxisValue>> axis;

  std::map<std::string, bool> actionValues;
  std::map<std::string, AxisValue> axisValues;

  std::map<std::string, TArray<ActionCallback>> actionBindings;
  std::map<std::string, TArray<AxisCallback>> axisBindings;

  InputRegistrar registrar;
  const InputProvider *provider;
public:
  InputHandler(const InputProvider *provider);

  void RegisterAction(InputKey key, const std::string &name);

  void RegisterAxis(InputKey key, const std::string &name, AxisValue value);

  void UpdateInputs();

  void Tick(double delta);

  inline InputRegistrar &GetRegistrar() { return registrar; }

};

}
