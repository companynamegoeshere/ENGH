
#include <input/input_registrar.hpp>
#include <input/input_handler.hpp>

ENGH::Input::InputRegistrar::InputRegistrar(InputHandler &input) : input(input) {}

void ENGH::Input::InputRegistrar::BindAction(const std::string &name, ENGH::Input::ActionCallback callback) {
  input.actionBindings[name] += callback;
}

void ENGH::Input::InputRegistrar::BindAxis(const std::string &name, ENGH::Input::AxisCallback callback) {
  input.axisBindings[name] += callback;
}
