#include <eobject/component/box_component.hpp>
#include <eobject/render/box.hpp>
#include <eobject/render/standard_shaders.hpp>

using ENGH::EObject::Render::Box;
using ENGH::EObject::Render::StandardShaders;
using ENGH::Render::RenderCommand;

inline static RenderCommand *getCommand() {
  static RenderCommand commandCache = {
      Box::INSTANCE->array.get(),
      StandardShaders::INSTANCE->flatColor.get()
  };
  return &commandCache;
}

void ENGH::EObject::Comps::BoxComponent::Render(ENGH::Render::RenderDispatcher &dispatcher) const {
  Component::Render(dispatcher);
  dispatcher.Dispatch(getCommand());
}
