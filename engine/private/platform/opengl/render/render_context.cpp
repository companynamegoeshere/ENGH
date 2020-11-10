#include <platform/opengl/render/render_context.hpp>
#include <platform/opengl/render/fragment_shader.hpp>
#include <platform/opengl/render/index_buffer.hpp>
#include <platform/opengl/render/vertex_array.hpp>
#include <platform/opengl/render/vertex_buffer.hpp>
#include <platform/opengl/render/vertex_shader.hpp>

#include <fstream>

using namespace ENGH::Platform::Render;
using namespace ENGH::Platform::Render::OpenGL;

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

  ProgramShader::DEBUG_SHADER = CreateShader(
      readFile("shaders/flat_vert.glsl"),
      readFile("shaders/flat_frag.glsl")
  );
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
