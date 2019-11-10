#include <iostream>
#include <platform/window.hpp>
#include <core/math.hpp>

using ENGH::Logger;
using ENGH::Math::MatrixX;
using ENGH::Platform::Render::BufferDataTypes;
using ENGH::Platform::Render::RenderLibrary;
using ENGH::Platform::Window;

int main() {
  Logger::getCoreLogger().SetLevel(Logger::Level::ALL);

  auto window = Window::CreateWindow(
      {
          "ASD",
          800, 600
      },
      RenderLibrary::OPENGL
  );
  window->Init();
  auto context = window->GetContext();
  auto renderer = context->GetRenderer();

  auto vertex = context->CreateVertexBuffer();
  vertex->SetData({
                      -0.8f, -0.8f, 2.0f, 0.0f, 1.0f,
                      +0.0f, +0.8f, 1.4f, 2.0f, 1.0f,
                      +0.8f, -0.8f, 0.3f, 1.0f, 0.8f
                  });
  vertex->SetLayout(
      {
          {"a_Position", BufferDataTypes::FLOAT2},
          {"a_Color", BufferDataTypes::FLOAT3},
      }
  );

  auto index = context->CreateIndexBuffer();
  index->SetData({0, 1, 2});

  auto array = context->CreateVertexArray();
  array->AddVertexBuffer(vertex);
  array->SetIndexBuffer(index);

  std::string vertexSrc =
      "#version 300 es\nprecision mediump float;\n\nlayout(location = 0) in vec2 a_Position;\nlayout(location = 1) in vec3 a_Color;\nout vec2 pos;\nout vec3 color;\nvoid main() {\n    pos = a_Position;\n    color = a_Color;\n    gl_Position = vec4(a_Position, 0.0, 1.0);\n}\n";

  std::string fragmentSrc =
      "#version 300 es\nprecision mediump float;\n\nlayout(location = 0) out vec4 fragColor;\nin vec2 pos;\nin vec3 color;\nuniform float time;\nvoid main() {\n    fragColor = vec4(pos * sin(time) + 0.5, 0.0, 0.0) * vec4(color, 1.0);\n}";

  auto program = context->CreateShader(vertexSrc, fragmentSrc);

  window->Loop([&](float delta) {
    renderer->Clear(0.2f, 0.2f, 0.2f, 1.0f);
    program->Bind();
    program->SetUniformFloat("time", delta);
    renderer->DrawVertexArray(array);
    context->SwapBuffers();
  });
}
