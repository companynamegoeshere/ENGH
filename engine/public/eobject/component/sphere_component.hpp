#pragma once

#include <eobject/component/component.hpp>

namespace ENGH::EObject::Render {
class Sphere;
}

namespace ENGH::EObject::Comps {

class SphereComponent : public Component {
  std::shared_ptr<Render::Sphere> sphere;
  uint32 lastLat = 0;
  uint32 lastLong = 0;
public:
  SphereComponent(uint32 latCount = 40, uint32 longCount = 40);

  uint32 latCount;
  uint32 longCount;

  void Render(ENGH::Render::RenderDispatcher &dispatcher) override;

};

}
