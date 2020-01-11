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

  virtual void Render(ENGH::Render::RenderDispatcher &dispatcher) const;

  template<typename T>
  T *AttachComponent() {
    T *t = new T();
    t->parent = this;
    children += t;
    return t;
  }

  inline Math::Mat4 GetTransformMatrix() const {
    Math::Mat4 base = parent != nullptr ? parent->GetTransformMatrix() : Math::Mat4::Identity();
    return base * transform.ToMatrix();
  };

};

}
