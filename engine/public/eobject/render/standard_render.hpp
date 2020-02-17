#pragma once

#include <eobject/object.hpp>
#include <eobject/component/component.hpp>
#include <platform/render/vertex_array.hpp>

namespace ENGH::EObject::Render {

class StandardRender : EObject {
  static StandardRender instance;
  StandardRender();
public:
  static inline StandardRender &Get() {
    return instance;
  }

  void RenderStaticMesh(
      const Comps::Component &comp,
      ENGH::Render::RenderDispatcher &dispatcher,
      Platform::Render::VertexArray *vert,
      Platform::Render::ProgramShader *shader);
};

}
