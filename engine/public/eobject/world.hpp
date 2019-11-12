#pragma once
#include <eobject/actor.hpp>
#include <eobject/object.hpp>

namespace ENGH::Render {
class WorldRenderer;
}

namespace ENGH::EObject {

class World : public EObject {

  friend class Render::WorldRenderer;

  Actor *SpawnExistingActor(Actor *actor);

protected:
  TArray<Actor *> tickingActorList;
  TArray<Actor *> actorList;

  float delta;

public:

  template<typename T>
  T *SpawnActor() {
    return reinterpret_cast<T *>(SpawnExistingActor(new T()));
  }

  void BeginPlay();

  void EndPlay();

  void Tick(float D);

  inline float GetDelta() { return delta; }

};

}
