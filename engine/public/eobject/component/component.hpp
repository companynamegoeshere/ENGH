#pragma once

#include <eobject/object.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::EObject {
class Actor;
}
namespace ENGH::EObject::Comps {
class SceneComponent;
}

namespace ENGH::EObject::Comps {

class Component : public EObject {
  friend class ::ENGH::EObject::Actor;
protected:
  Actor          *owner;
  SceneComponent *parent = nullptr;

};

}
