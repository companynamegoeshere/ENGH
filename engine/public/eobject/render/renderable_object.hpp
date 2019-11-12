#pragma once

#include <eobject/object.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::EObject::Render {

class RenderableObject : EObject {
  RenderableObject();

  static TArray<RenderableObject *> list;

protected:
  template<typename T>
  static T *Instantiate() {
    T *t = new T();
    list += t;
    return t;
  }

public:

  inline static TArray<RenderableObject *> GetList() {
    return list;
  }

  virtual void SetupRender(ENGH::Platform::Render::RenderContext &context) = 0;

  virtual void ShutdownRender(ENGH::Platform::Render::RenderContext &context) = 0;
};

}
