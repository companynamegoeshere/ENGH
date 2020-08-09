#pragma once

#include <eobject/component/primitive_component.hpp>

namespace ENGH::Render::Component {

class PrimitiveRenderDelegate {
  EObject::Comps::PrimitiveComponent *primitive;
public:
  PrimitiveRenderDelegate(EObject::Comps::PrimitiveComponent *primitive);

  virtual ~PrimitiveRenderDelegate() = 0;

  virtual bool IsDirty();
};

}