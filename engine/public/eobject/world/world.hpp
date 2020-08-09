#pragma once

#include <eobject/object.hpp>

#include <eobject/world/world_registry.hpp>

namespace ENGH::Render {
class WorldRenderer;
}

namespace ENGH::EObject {
class Actor;
}

namespace ENGH::EObject::World {

class TickTarget;

class World : public EObject {

  friend class Render::WorldRenderer;
  friend class TickTarget;

  WorldRegistry registry;

  Actor *SpawnExistingActor(Actor *actor);

protected:
  TSet<TickTarget *> tickingList;
  TArray<Actor *> actorList;

  double delta;

public:

  template<typename T, typename... Args>
  inline T *SpawnActor(Args &&...args) {
    return reinterpret_cast<T *>(SpawnExistingActor(new T(std::forward<Args>(args)...)));
  }

  void BeginPlay();

  void EndPlay();

  void Tick(double delta);

  inline double GetDelta() { return delta; }

};

}
