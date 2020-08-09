#include <eobject/actor.hpp>

namespace ENGH::EObject {

Actor::Actor() : root(new Comps::SceneComponent) {
  root->owner = this;
}

Actor::~Actor() {
  delete root;
}

void Actor::BeginPlay() {}

void Actor::EndPlay() {}

void Actor::Tick(float delta) {}

void Actor::SetRootComponent(ENGH::EObject::Comps::SceneComponent *sceneComp, bool alsoDelete) {
  if (alsoDelete) {
    delete root;
  }
  root = sceneComp;
  root->owner  = this;
  root->parent = nullptr;
  auto iter = [this](const TArray<Comps::Component *> &list, auto call) -> void {
    for (const auto &c : list) {
      c->owner = this;
      Comps::SceneComponent *sc = dynamic_cast<Comps::SceneComponent *>(c);
      if (sc) {
        call(sc->children, call);
      }
    }
  };
  iter(root->children, iter);
}
void Actor::SetupTickFunction(bool isRegistering, bool components) {
  if (isRegistering) {
    actorTickTarget.target = this;
    actorTickTarget.RegisterFunction(world);
    if (components) {
      root->Traverse([](Comps::Component *c) {
        c->SetupTickFunction(true);
        return true;
      });
    }
  } else {
    actorTickTarget.UnregisterFunction();
    root->Traverse([](Comps::Component *c) {
      c->SetupTickFunction(false);
      return true;
    });
  }
}

void Actor::RegisterWorldFunctions(World::WorldRegistry& registry) {
  GetRoot()->Traverse([&registry](Comps::Component *c) {
    c->RegisterWorldFunctions(registry);
    return true;
  });
}

void World::ActorTickTarget::ExecuteTick(float deltaTime) {
  this->target->Tick(deltaTime);
}

}
