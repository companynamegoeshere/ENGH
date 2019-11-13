#pragma once

#include <eobject/object.hpp>
#include <eobject/world.hpp>

namespace ENGH::EObject {

namespace Comps {
class Component;
}

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

  virtual void BeginPlay();

  virtual void EndPlay();

  virtual void Tick();

};

}
