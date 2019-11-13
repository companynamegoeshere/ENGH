#pragma once

#include <eobject/object.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::EObject::Render {

class RenderableObject : EObject {

protected:
  template<typename T>
  static T *Instantiate() {
    T *t = new T();
    GetList() += t;
    return t;
  }

  RenderableObject();

public:

  static TArray<RenderableObject *> &GetList() {
    static TArray<RenderableObject *> list;
    return list;
  }

  virtual void SetupRender(ENGH::Platform::Render::RenderContext &context) = 0;

  virtual void ShutdownRender(ENGH::Platform::Render::RenderContext &context) = 0;
};

}
