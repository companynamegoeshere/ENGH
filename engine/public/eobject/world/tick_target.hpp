#pragma once

#include <eobject/object.hpp>

namespace ENGH::EObject::World {

class World;

class TickTarget {
  World *world = nullptr;
public:
  bool enableTicking: 1;

  TickTarget() { enableTicking = false; }

  virtual void ExecuteTick(float deltaTime) = 0;

  virtual void RegisterFunction(World *world);

  virtual void UnregisterFunction();
};

}
