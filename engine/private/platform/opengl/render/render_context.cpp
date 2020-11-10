#include <platform/opengl/render/render_context.hpp>
#include <platform/opengl/render/fragment_shader.hpp>
#include <platform/opengl/render/index_buffer.hpp>
#include <platform/opengl/render/vertex_array.hpp>
#include <platform/opengl/render/vertex_buffer.hpp>
#include <platform/opengl/render/vertex_shader.hpp>

#include <util/file/fs.hpp>

#include <fstream>

using namespace ENGH::Platform::Render;
using namespace ENGH::Platform::Render::OpenGL;

using ENGH::Util::File::readFile;

OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *window) : window(window) {}

void OpenGLRenderContext::Setup() {
  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    ENGH_CORE_FATAL("could not load opengl extensions");
  }
  renderer = std::make_shared<OpenGLRenderer>();
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  screenFrameBuffer = std::make_shared<OpenGLFrameBuffer>(FrameBuffer::BufferType::NONE, width, height, 0);
  glEnable(GL_DEPTH_TEST);

  auto setupShader = [&](std::shared_ptr<ProgramShader>& shader, const char* name) {
    auto vName = std::string("shaders/") + name + "_vert.glsl";
    auto fName = std::string("shaders/") + name + "_frag.glsl";
    auto vData = readFile(vName);
    if(!vData) {
      ENGH_CORE_ERROR("Could not read shader vertex file: ", vName);
      return;
    }
    auto fData = readFile(fName);
    if(!fData) {
      ENGH_CORE_ERROR("Could not read shader vertex file: ", fName);
      return;
    }
    shader = CreateShader(*vData, *fData);
  };
  setupShader(ProgramShader::DEBUG_SHADER, "flat");
}

OpenGLRenderContext::~OpenGLRenderContext() {}

void OpenGLRenderContext::SwapBuffers() {
  glfwSwapBuffers(window);
}

std::shared_ptr<IndexBuffer> OpenGLRenderContext::CreateIndexBuffer() {
  return std::make_shared<OpenGLIndexBuffer>();
}

std::shared_ptr<VertexBuffer> OpenGLRenderContext::CreateVertexBuffer() {
  return std::make_shared<OpenGLVertexBuffer>();
}

std::shared_ptr<VertexArray> OpenGLRenderContext::CreateVertexArray() {
  return std::make_shared<OpenGLVertexArray>();
}

std::shared_ptr<ProgramShader> OpenGLRenderContext::CreateShader(const std::string &vertex,
                                                                 const std::string &fragment) {
  auto                         prog = std::make_shared<Shader::OpenGLProgramShader>();
  Shader::OpenGLVertexShader   vert(vertex);
  Shader::OpenGLFragmentShader frag(fragment);
  prog->Attach(vert, frag);
  return prog;
}

std::shared_ptr<FrameBuffer> OpenGLRenderContext::CreateFrameBuffer(FrameBuffer::BufferType type, uint32 width, uint32 height) {
  auto fb = std::make_shared<OpenGLFrameBuffer>(type, width, height);
  fb->Invalidate();
  return fb;
}

std::shared_ptr<FrameBuffer> OpenGLRenderContext::GetScreenFrameBuffer() {
  return screenFrameBuffer;
}

std::shared_ptr<Renderer> OpenGLRenderContext::GetRenderer() {
  return this->renderer;
}
