#include <eobject/world.hpp>

void ENGH::EObject::World::BeginPlay() {
  for (Actor *actor : actorList) {
    actor->BeginPlay();
  }
}

void ENGH::EObject::World::EndPlay() {
  for (Actor *actor : actorList) {
    actor->EndPlay();
  }
}

void ENGH::EObject::World::Tick(float delta) {
  this->delta = delta;
  for (Actor *actor : tickingActorList) {
    actor->Tick();
  }
}

ENGH::EObject::Actor *ENGH::EObject::World::SpawnExistingActor(Actor *actor) {
  actor->world = this;
  actorList += actor;
  if (actor->tickingEnabled) {
    tickingActorList += actor;
  }
  return actor;
}
