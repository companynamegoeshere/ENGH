#pragma once

#include <eobject/render/renderable_object.hpp>

namespace ENGH::EObject::Render {

class StandardShaders : public RenderableObject {
  static StandardShaders *instance;
public:
  static inline StandardShaders &Get() {
    return *instance;
  }

  std::shared_ptr<Platform::Render::ProgramShader> flatColor;

  void SetupRender(ENGH::Platform::Render::RenderContext &context) override;

  void ShutdownRender(ENGH::Platform::Render::RenderContext &context) override;

};

}
