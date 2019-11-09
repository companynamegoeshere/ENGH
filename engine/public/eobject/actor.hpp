#pragma once

#include <eobject/object.hpp>
#include <math/vec3.hpp>

namespace ENGH::EObject {

class Actor : EObject {

protected:

  std::unique_ptr<class Component> root;

public:

  Actor();

  virtual void BeginPlay(bool &overrideTicking);

  virtual void EndPlay();

  virtual void Tick() = 0;

};

}
