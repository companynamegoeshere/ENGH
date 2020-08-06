#include <eobject/actor.hpp>
#include <eobject/component/component.hpp>

namespace ENGH::EObject {

Comps::Component::Component() {
}

void Comps::Component::Tick(float delta) {}

void Comps::Component::SetupTickFunction(bool isRegistering) {
  if (isRegistering) {
    componentTickTarget.target = this;
    componentTickTarget.RegisterFunction(owner->GetWorld());
  } else {
    componentTickTarget.UnregisterFunction();
  }
}

void World::ComponentTickTarget::ExecuteTick(float deltaTime) {
  this->target->Tick(deltaTime);
}

}
