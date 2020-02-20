#pragma once

#include <eobject/object.hpp>
#include <platform/render/render_context.hpp>

namespace ENGH::EObject::Render {

class RenderableObject : EObject {

protected:
  template<typename T, typename ...Args>
  static T *Instantiate(Args &&...args) {
    T *t = new T(std::forward<Args>(args)...);
    if(currentContext != nullptr) {
      t->SetupRender(*currentContext);
    } else {
      GetList() += t;
    }
    return t;
  }

  RenderableObject();

public:

  static ENGH::Platform::Render::RenderContext *currentContext;

  static TArray<RenderableObject *> &GetList() {
    static TArray<RenderableObject *> list;
    return list;
  }

  virtual void SetupRender(ENGH::Platform::Render::RenderContext &context) = 0;

  virtual void ShutdownRender(ENGH::Platform::Render::RenderContext &context) = 0;
};

}
