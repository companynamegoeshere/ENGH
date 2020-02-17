#include <eobject/render/standard_shaders.hpp>
#include <fstream>

static std::string readFile(const char *fileName) {
  std::ifstream in(fileName, std::ios::in | std::ios::ate | std::ios::binary);
  if (!in) {
    ENGH_CORE_ERROR("Could not read shader file: ", fileName);
    return "";
  }
  std::string data;
  data.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&data[0], data.size());
  in.close();
  return data;
}

namespace ENGH::EObject::Render {

StandardShaders* StandardShaders::instance = RenderableObject::Instantiate<StandardShaders>();

void ENGH::EObject::Render::StandardShaders::SetupRender(ENGH::Platform::Render::RenderContext &context) {
  this->flatColor = context.CreateShader(
      readFile("shaders/flat_vert.glsl"),
      readFile("shaders/flat_frag.glsl")
  );
  ENGH_CORE_FINEST("Standard shaders loaded");
}
void ENGH::EObject::Render::StandardShaders::ShutdownRender(ENGH::Platform::Render::RenderContext &context) {

}

}
