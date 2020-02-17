#include <eobject/render/standard_render.hpp>

using ENGH::Platform::Render::ProgramShader;
using ENGH::Platform::Render::IndexBuffer;
using ENGH::Platform::Render::VertexArray;

namespace ENGH::EObject::Render {

StandardRender StandardRender::instance;

StandardRender::StandardRender() {}

void StandardRender::RenderStaticMesh(const Comps::Component *comp,
                                      ENGH::Render::RenderDispatcher &dispatcher,
                                      VertexArray *vert,
                                      IndexBuffer *index,
                                      ProgramShader *shader) {
  auto transform = comp->GetTransformMatrix();
  auto filter    = dispatcher.GetMatrixTransformer();
  auto final     = filter(transform);
  dispatcher.Dispatch(
      {
          vert,
          index,
          shader,
          [final](ProgramShader *shader) {
            shader->SetUniformMat4("transform", &final[0], true);
          }
      }
  );
}

}
