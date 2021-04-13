#include <eobject/component/scene_component.hpp>

namespace ENGH::EObject::Comps {

void SceneComponent::RegisterWorldFunctions() {
  Component::RegisterWorldFunctions();
  this->Traverse([](Component *c) {
    c->RegisterWorldFunctions();
    return true;
  }, false);
}

//void SceneComponent::Traverse(smallfun::SmallFun<bool(Component *), 128> target, bool receiveSelf) {
void SceneComponent::Traverse(std::function<bool(Component *)> target, bool receiveSelf) {
  if (receiveSelf) {
    if (!target(this)) {
      return;
    }
  }
  auto iter = [&target](const auto &list, const auto &iter) -> bool {
    for (const auto &e : list) {
      if (!target(e)) {
        return false;
      }
      SceneComponent *sc = dynamic_cast<SceneComponent *>(e);
      if (sc) {
        if (!iter(sc->children, iter)) {
          return false;
        }
      }
    }
    return true;
  };
  iter(children, iter);
}

}
