#pragma once

#include <eobject/object.hpp>
#include <eobject/world.hpp>
#include <eobject/component/component.hpp>

namespace ENGH::EObject {

class Actor : EObject {

protected:

  std::unique_ptr<Comps::Component> root;

public:

  World *world;

  bool tickingEnabled;

  Actor();

  inline Comps::Component *GetRoot() {
    return root.get();
  };

  template<typename T, typename ...Args>
  inline T *SetRoot(Args && ...args) {
    root.reset(new T(std::forward<Args>(args)...));
    return reinterpret_cast<T *>(GetRoot());
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
