#include <platform/opengl/render/render_context.hpp>
#include <platform/opengl/render/fragment_shader.hpp>
#include <platform/opengl/render/index_buffer.hpp>
#include <platform/opengl/render/program_shader.hpp>
#include <platform/opengl/render/vertex_array.hpp>
#include <platform/opengl/render/vertex_buffer.hpp>
#include <platform/opengl/render/vertex_shader.hpp>

using namespace ENGH::Platform::Render;
using namespace ENGH::Platform::Render::OpenGL;

OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *window) : window(window) {}

void OpenGLRenderContext::Setup() {
    glfwMakeContextCurrent(window);
    if (! gladLoadGL(glfwGetProcAddress)) {
        ENGH_CORE_FATAL("could not load opengl extensions");
    }
    renderer = std::make_shared<OpenGLRenderer>();
  glEnable(GL_DEPTH_TEST);
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
    auto prog = std::make_shared<Shader::OpenGLProgramShader>();
    Shader::OpenGLVertexShader vert(vertex);
    Shader::OpenGLFragmentShader frag(fragment);
    prog->Attach(vert, frag);
    return prog;
}

std::shared_ptr<Renderer> OpenGLRenderContext::GetRenderer() {
    return this->renderer;
}
