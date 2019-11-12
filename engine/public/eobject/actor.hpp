#pragma once

#include <eobject/object.hpp>
#include <eobject/world.hpp>

namespace ENGH::EObject {

class Actor : EObject {

protected:

  std::unique_ptr<class Component> root;

public:

  World *world;

  bool tickingEnabled;

  Actor();

  inline Component *GetRoot() {
    return &*root;
  };

  virtual void BeginPlay();

  virtual void EndPlay();

  virtual void Tick();

};

}
