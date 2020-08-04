#pragma once

#include <eobject/component/component.hpp>
#include <eobject/data/transform.hpp>

namespace ENGH::EObject::Comps {

class SceneComponent : public Component {
  friend class ::ENGH::EObject::Actor;
protected:
  TArray<Component *> children;
public:
  Data::Transform transform;

  template<typename T, typename ...Args>
  T &AttachComponent(Args &&...args) {
    T *t = new T(std::forward<Args>(args)...);
    t->owner  = this->owner;
    t->parent = this;
    children += t;
    return *t;
  }

  inline Math::Mat4 GetWorldMatrix() const {
    if (parent != nullptr) {
      return parent->transform * transform;
    } else {
      return transform;
    }
  };

};

}
