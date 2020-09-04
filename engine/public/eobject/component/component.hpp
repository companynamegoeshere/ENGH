#pragma once

#include <eobject/object.hpp>
#include <render/render_dispatcher_proxy.hpp>
#include <eobject/world/tick_target.hpp>

namespace ENGH::EObject {
class Actor;
}
namespace ENGH::EObject::Comps {
class Component;
class SceneComponent;
}

namespace ENGH::EObject::World {

class WorldRegistry;

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

  virtual void Tick(float delta);

  virtual void SetupTickFunction(bool isRegistering);

  virtual void RegisterWorldFunctions();
};

}
