#pragma once
#include <eobject/actor.hpp>
#include <eobject/object.hpp>

namespace ENGH::EObject {

class World : public EObject {

protected:
  TArray<Actor *> tickingActorList;
public:

  TArray<Actor *> actorList;

  void BeginPlay();

  void EndPlay();

  void Tick();

};

}
