#pragma once

#include <eobject/object.hpp>
#include <eobject/component/component.hpp>
#include <platform/render/index_buffer.hpp>
#include <platform/render/vertex_array.hpp>

namespace ENGH::EObject::Render {

class StandardRender : EObject {
public:

  static void RenderStaticMesh(
      const Comps::Component *comp,
      ENGH::Render::RenderDispatcher &dispatcher,
      Platform::Render::VertexArray *vert,
      Platform::Render::IndexBuffer *index,
      Platform::Render::ProgramShader *shader);
};

}
