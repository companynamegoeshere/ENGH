#include <eobject/actor.hpp>
#include <eobject/component/component.hpp>

ENGH::EObject::Actor::Actor() :
    root(std::make_unique<Component>()) {}

void ENGH::EObject::Actor::BeginPlay(bool &overrideTicking) {}

void ENGH::EObject::Actor::EndPlay() {}
