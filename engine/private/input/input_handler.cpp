#include <input/input_handler.hpp>

namespace ENGH::Input {

InputHandler::InputHandler(InputProvider *provider) :
    registrar(*this),
    provider(provider) {}

void InputHandler::RegisterAction(InputKey key, const std::string &name) {
  actions += std::make_pair(key, name);
}

void InputHandler::RegisterAxis(InputKey key, const std::string &name, AxisValue value) {
  axis += std::make_tuple(key, name, value);
}

void InputHandler::UpdateInputs() {
  auto &provider = *this->provider;
  for (const auto &entry : actions) {
    actionValues[entry.second] = provider.isPressed(entry.first);
  }
  for (auto &entry: axisValues) { // Reset axis value
    entry.second = 0;
  }
  for (const auto &entry: axis) {
    if (provider.isPressed(std::get<0>(entry))) {
      axisValues[std::get<1>(entry)] += std::get<2>(entry);
    }
  }
}

void InputHandler::Tick(double delta) {
  for (const auto &entry : actionBindings) {
    bool value = actionValues[entry.first];
    for (const auto &callback : entry.second) {
      callback(value, delta);
    }
  }

  for (const auto &entry : axisBindings) {
    AxisValue value = axisValues[entry.first];
    for (const auto &callback : entry.second) {
      callback(value, delta);
    }
  }
}

}
