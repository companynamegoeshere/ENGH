#pragma once

#include <eobject/object.hpp>
#include <eobject/data/transform.hpp>
#include <render/render_dispatcher.hpp>

namespace ENGH::Render {
  class WorldRenderer;
}

namespace ENGH::EObject::Comps {

class Component : EObject {
  friend ::ENGH::Render::WorldRenderer;
protected:
  Component *parent = nullptr;
  TArray<Component *> children;
public:
  Data::Transform transform;

  template<typename T, typename ...Args>
  T *AttachComponent(Args && ...args) {
    T *t = new T(std::forward<Args>(args)...);
    t->parent = this;
    children += t;
    return t;
  }

  virtual void Render(ENGH::Render::RenderDispatcher &dispatcher);

  inline Math::Mat4 GetTransformMatrix() const {
    Math::Mat4 base = parent != nullptr ? parent->GetTransformMatrix() : Math::Mat4::Identity();
    return base * transform.ToMatrix();
  };

};

}
