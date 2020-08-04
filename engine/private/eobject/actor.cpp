#include <eobject/actor.hpp>

namespace ENGH::EObject {

Actor::Actor() :
    root(new Comps::SceneComponent) {}

void Actor::SetRoot(ENGH::EObject::Comps::SceneComponent *sceneComp) {
  delete root;
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

void Actor::BeginPlay() {}

void Actor::EndPlay() {}

void Actor::Tick() {}

}
