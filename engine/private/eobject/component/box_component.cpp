#include <eobject/component/box_component.hpp>
#include <eobject/render/box.hpp>
#include <eobject/render/standard_shaders.hpp>

using ENGH::EObject::Render::Box;
using ENGH::EObject::Render::StandardShaders;

void ENGH::EObject::Comps::BoxComponent::Render(ENGH::Render::RenderDispatcher &dispatcher) const {
  Component::Render(dispatcher);
  dispatcher.Dispatch({
                          Box::INSTANCE->array.get(),
                          StandardShaders::INSTANCE->flatColor.get()
                      });
}
