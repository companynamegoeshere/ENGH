#include <eobject/component/component.hpp>

void ENGH::EObject::Component::Render(const ENGH::Render::RenderDispatcher &dispatcher) const {
  for (const auto &child : children) {
    child->Render(dispatcher);
  }
}
