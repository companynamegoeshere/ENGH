#pragma once

#include <eobject/object.hpp>
#include <eobject/data/transform.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::EObject::Comps {

class Component : EObject {

public:
  Data::Transform transform;

  TArray<Component *> children;

  virtual void Render(ENGH::Render::RenderDispatcher &dispatcher) const;

};

}
