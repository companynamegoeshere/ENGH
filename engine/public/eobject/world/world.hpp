#pragma once

#include <core/math.hpp>
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

  double delta = 0.0;

public:

  Math::Vec3 ClearColor = {0.2f, 0.2f, 0.2f};

  template<typename T, typename... Args>
  inline T *SpawnActor(Args &&...args) {
    static_assert(std::is_base_of_v<Actor, T>, "T is not a Actor subclass");
    return reinterpret_cast<T *>(SpawnExistingActor(new T(std::forward<Args>(args)...)));
  }

  World();

  void BeginPlay();

  void EndPlay();

  void Tick(double delta);

  inline double GetDelta() const { return delta; }

  WorldRegistry& GetRegistry();
};

}
