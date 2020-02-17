#pragma once

#include <eobject/component/component.hpp>

namespace ENGH::EObject::Comps {

class SphereComponent : public Component {

public:
  void Render(ENGH::Render::RenderDispatcher &dispatcher) const override;

};

}
