#pragma once

#include <eobject/component/component.hpp>
#include <eobject/data/transform.hpp>

namespace ENGH::EObject::Comps {

class SceneComponent : public Component {
  friend class ::ENGH::EObject::Actor;

protected:
  TArray<Component *> children;
public:

  typedef TArray<Component *>::iterator iterator;
  typedef TArray<Component *>::const_iterator const_iterator;

  Data::Transform transform;

  template<typename T, typename ...Args>
  T *AttachComponent(Args &&...args) {
    static_assert(std::is_base_of_v<Component, T>, "T is not a Component subclass");
    T *t = new T(std::forward<Args>(args)...);
    t->owner = this->owner;
    t->parent = this;
    children += t;
    t->RegisterWorldFunctions();
    return t;
  }

  inline Math::Mat4 GetWorldMatrix() const {
    if (parent != nullptr) {
      return parent->GetWorldMatrix() * transform;
    } else {
      return transform;
    }
  };

  void RegisterWorldFunctions() override;

  inline void Traverse(const std::function<bool(Component *)> &target) {
    Traverse(target, true);
  }

  virtual void Traverse(const std::function<bool(Component *)> &target, bool receiveSelf);

  inline iterator begin() { return children.begin(); }

  inline const_iterator begin() const { return children.begin(); }

  inline iterator end() { return children.end(); }

  inline const_iterator end() const { return children.end(); }

};

}
