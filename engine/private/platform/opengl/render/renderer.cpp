#include <platform/opengl/render/renderer.hpp>
#include <glad/gl.h>

namespace ENGH::Platform::Render::OpenGL {

void OpenGLRenderer::Clear(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRenderer::DrawVertexArray(const std::shared_ptr<VertexArray> &array) {
  array->Bind();
  glDrawElements(GL_TRIANGLES, array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
OpenGLRenderer::~OpenGLRenderer() {}

}