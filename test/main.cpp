#include <iostream>
#include <platform/window.hpp>
#include <eobject/actor.hpp>
#include <eobject/world.hpp>
#include <eobject/component/box_component.hpp>
#include <render/world_renderer.hpp>
#include <core/math.hpp>

using ENGH::Logger;
using ENGH::EObject::Actor;
using ENGH::EObject::Comps::BoxComponent;
using ENGH::EObject::Comps::Component;
using ENGH::EObject::World;
using ENGH::Platform::Render::BufferDataTypes;
using ENGH::Platform::Render::RenderLibrary;
using ENGH::Platform::Window;
using ENGH::Render::WorldRenderer;

int main() {
  Logger::getCoreLogger().SetLevel(Logger::Level::ALL);
  ENGH_INFO("Test application");

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

  auto world = new World();

  auto worldRenderer = new WorldRenderer(world, context);

  auto *actor = world->SpawnActor<Actor>();
  actor->GetRoot()->children += new BoxComponent();

  world->BeginPlay();
  window->Loop([&](double delta, double total) {
    renderer->Clear(0.2f, 0.2f, 0.2f, 1.0f);
    world->Tick(delta);
    worldRenderer->SetupRender();
    worldRenderer->Render();
    context->SwapBuffers();
  });

  /*auto context = window->GetContext();
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
  });*/
}
