#pragma once

#include <eobject/object.hpp>
#include <eobject/tick_target.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::EObject {
class Actor;
}
namespace ENGH::EObject::Comps {
class Component;
class SceneComponent;
}

namespace ENGH::EObject::World {
class ComponentTickTarget : public TickTarget {
  friend class ::ENGH::EObject::Comps::Component;
  Comps::Component *target;
public:
  void ExecuteTick(float deltaTime) override;
};
}

namespace ENGH::EObject::Comps {

class Component : public EObject {
  friend class ::ENGH::EObject::Actor;
protected:
  Actor          *owner;
  SceneComponent *parent = nullptr;

  World::ComponentTickTarget componentTickTarget;
public:

  Component();

  void Tick(float delta);

  void SetupTickFunction(bool isRegistering);

};

}
