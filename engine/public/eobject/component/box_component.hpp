#pragma once

#include <eobject/component/component.hpp>

namespace ENGH::EObject::Comps {

class BoxComponent : public Component {

public:
  void Render(ENGH::Render::RenderDispatcher &dispatcher) const override;

};

}
