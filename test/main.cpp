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

using namespace ENGH::Math;

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

  BoxComponent *comp = new BoxComponent();
  actor->GetRoot()->children += comp;

  comp->transform.scale *= 0.4;

  world->BeginPlay();
  window->Loop([&](double delta, double total) {
    renderer->Clear(0.2f, 0.2f, 0.2f, 1.0f);
    world->Tick(delta);
    comp->transform.position.x = sin(total) * 0.2;
    comp->transform.position.y = cos(total) * 0.2;
    comp->transform.rotation = comp->transform.rotation * Quat::FromEulerAngles(delta * 10 * DEGtoRAD, 0, delta * 30 * DEGtoRAD);
    worldRenderer->SetupRender();
    worldRenderer->Render();
    context->SwapBuffers();
  });
}
