#include <eobject/actor.hpp>
#include <eobject/component/sub_component.hpp>

ENGH::Actor::Actor() {
    root = new SubComponent();
}

void ENGH::Actor::BeginPlay() {}

void ENGH::Actor::EndPlay() {}
