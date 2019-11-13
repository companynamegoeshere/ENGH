#pragma once

#include <platform/render/renderer.hpp>

namespace ENGH::Platform::Render::OpenGL {

class OpenGLRenderer : public Renderer {
public:

  void Clear(float r, float g, float b, float a) override;

  void DrawVertexArray(VertexArray *array) override;

  ~OpenGLRenderer() override;
};

}
