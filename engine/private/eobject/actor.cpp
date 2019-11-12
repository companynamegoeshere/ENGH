#include <eobject/actor.hpp>
#include <eobject/component/component.hpp>

ENGH::EObject::Actor::Actor() :
    root(std::make_unique<Component>()) {}

void ENGH::EObject::Actor::BeginPlay() {}

void ENGH::EObject::Actor::EndPlay() {}

void ENGH::EObject::Actor::Tick() {}
