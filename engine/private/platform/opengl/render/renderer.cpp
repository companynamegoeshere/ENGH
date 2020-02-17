#include <platform/opengl/render/renderer.hpp>
#include <glad/gl.h>

namespace ENGH::Platform::Render::OpenGL {

void OpenGLRenderer::Clear(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRenderer::DrawVertexArray(VertexArray *array, IndexBuffer *indexBuffer) {
  array->Bind();
  indexBuffer->Bind();
  glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}
OpenGLRenderer::~OpenGLRenderer() {}

}