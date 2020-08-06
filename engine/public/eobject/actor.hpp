#pragma once

#include <eobject/object.hpp>
#include <eobject/tick_target.hpp>
#include <eobject/world.hpp>
#include <eobject/component/scene_component.hpp>
#include <eobject/component/component.hpp>

namespace ENGH::EObject {

namespace World {

class ActorTickTarget : public TickTarget {
  friend class ::ENGH::EObject::Actor;
  Actor *target;
public:
  void ExecuteTick(float deltaTime) override;
};

}

class Actor : EObject {
  friend class World::World;
protected:

  Comps::SceneComponent  *root;
  World::World           *world;
  World::ActorTickTarget actorTickTarget;

public:

  Actor();

  ~Actor();

  virtual void BeginPlay();

  virtual void EndPlay();

  virtual void Tick(float delta);

  void SetRootComponent(Comps::SceneComponent *sceneComp, bool alsoDelete = true);

  template<typename T, bool alsoDelete = true, typename ...Args>
  T &SetRootComponent(Args &&...args) {
    static_assert(std::is_base_of_v<Comps::SceneComponent, T>);
    SetRootComponent(new T(std::forward<Args>(args)...), alsoDelete);
    return reinterpret_cast<T &>(*root);
  }

  inline Comps::SceneComponent *GetRoot() {
    return root;
  };

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

  inline World::World* GetWorld() {
    return world;
  }

  void SetupTickFunction(bool isRegistering, bool components);

};

}
