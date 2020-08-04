#pragma once

#include <eobject/object.hpp>
#include <eobject/world.hpp>
#include <eobject/component/scene_component.hpp>

namespace ENGH::EObject {

class Actor : EObject {

protected:

  Comps::SceneComponent *root;

public:

  World *world;

  bool tickingEnabled;

  Actor();

  inline Comps::SceneComponent& GetRoot() {
    return *root;
  };

  void SetRoot(Comps::SceneComponent *sceneComp);

  template<typename T, typename ...Args>
  T &SetRoot(Args &&...args) {
    static_assert(std::is_base_of_v<Comps::SceneComponent, T>);
    _SetRoot(new T(std::forward<Args>(args)...));
    return reinterpret_cast<T &>(*root);
  }

  inline Data::Transform &GetTransform() {
    return root->transform;
  }

  inline Math::Vec3 &GetPosition() {
    return GetTransform().position;
  }

  inline Math::Quat &GetRotation() {
    return GetTransform().rotation;
  }

  inline Math::Vec3 &GetScale() {
    return GetTransform().scale;
  }

  virtual void BeginPlay();

  virtual void EndPlay();

  virtual void Tick();

};

}
