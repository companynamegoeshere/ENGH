#include <eobject/world/world.hpp>

#include <eobject/actor.hpp>
#include <eobject/world/tick_target.hpp>

namespace ENGH::EObject::World {

void World::BeginPlay() {
  for (Actor *actor : actorList) {
    actor->SetupTickFunction(true, true);
    actor->BeginPlay();
  }
}

void World::EndPlay() {
  for (Actor *actor : actorList) {
    actor->SetupTickFunction(false, true);
    actor->EndPlay();
  }
}

void World::Tick(double delta) {
  this->delta = delta;
  for (const auto& target : tickingList) {
    target->ExecuteTick(delta);
  }
}

Actor *World::SpawnExistingActor(Actor *actor) {
  actor->world = this;
  actorList += actor;
  actor->SetupTickFunction(true, true);
  actor->RegisterWorldFunctions(registry);
  return actor;
}

void TickTarget::RegisterFunction(World *world) {
  ASSERT(world != nullptr, "World must be not null");

  if(this->world != nullptr) {
    this->UnregisterFunction();
  }
  if(enableTicking) {
    this->world = world;
    this->world->tickingList += this;
  }
}

void TickTarget::UnregisterFunction() {
  this->world->tickingList -= this;
  this->world = nullptr;
}

}
