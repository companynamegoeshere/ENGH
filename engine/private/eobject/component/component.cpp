#include <eobject/component/component.hpp>

void ENGH::EObject::Comps::Component::Render(ENGH::Render::RenderDispatcher &dispatcher) const {
  for (const auto &child : children) {
    child->Render(dispatcher);
  }
}
