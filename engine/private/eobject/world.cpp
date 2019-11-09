#include <eobject/world.hpp>

void ENGH::EObject::World::BeginPlay() {
  for (Actor *actor : actorList) {
    bool ticking = true;
    actor->BeginPlay(ticking);
    if (ticking) {
      tickingActorList += actor;
    }
  }
}

void ENGH::EObject::World::EndPlay() {
  for (Actor *actor : actorList) {
    actor->EndPlay();
  }
}

void ENGH::EObject::World::Tick() {
  for (Actor *actor : tickingActorList) {
    actor->Tick();
  }
}
