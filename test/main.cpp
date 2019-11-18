#include <iostream>
#include <core/math.hpp>
#include <eobject/actor.hpp>
#include <eobject/world.hpp>
#include <eobject/component/box_component.hpp>
#include <input/input_handler.hpp>
#include <render/camera/perspective_camera.hpp>
#include <render/world_renderer.hpp>
#include <platform/window.hpp>
#include <platform/opengl/glfw_window.hpp>
#include <GLFW/glfw3.h>

using ENGH::Logger;
using ENGH::EObject::Actor;
using ENGH::EObject::Comps::BoxComponent;
using ENGH::EObject::Comps::Component;
using ENGH::EObject::World;
using ENGH::Input::InputKey;
using ENGH::Platform::Render::BufferDataTypes;
using ENGH::Platform::Render::RenderLibrary;
using ENGH::Platform::Window;
using ENGH::Render::Camera::PerspectiveCamera;
using ENGH::Render::WorldRenderer;

using namespace ENGH::Math;

/*bool logInit = false;
void *operator new(size_t size) {
  void* ptr = malloc(size);
  if(logInit) {
    ENGH_CORE_FINEST("Allocating ", size, " bytes at ", static_cast<long>((std::uintptr_t)ptr));
  }
  return ptr;
}

void operator delete(void *ptr, size_t size) {
  if(logInit) {
    ENGH_CORE_FINEST("Freeing at ", size, "bytes at ", static_cast<long>((std::uintptr_t)ptr));
  }
  return free(ptr);
}*/

int main() {
  Logger::getCoreLogger().SetLevel(Logger::Level::ALL);
//  logInit = true;
  ENGH_INFO("Test application");

  auto window = Window::CreateWindow(
      {
          "ASD",
          800, 600
      },
      RenderLibrary::OPENGL
  );
  window->Init();

  PerspectiveCamera *cam = new PerspectiveCamera();
  cam->fov = 80 * DEGtoRAD;
  cam->znear = 0.1;
  cam->zfar = 1000;
  window->SetResizeCallback([&cam](double width, double height) {
    cam->aspect = width / height;
  });

  auto input = ENGH::Input::InputHandler(window->GetInputProvider());

  auto context = window->GetContext();
  auto renderer = context->GetRenderer();

  auto world = new World();
  auto worldRenderer = new WorldRenderer(world, cam, context);
  auto &dispatcher = worldRenderer->GetDispatcher();

  auto *actor = world->SpawnActor<Actor>();

  BoxComponent *comp = actor->GetRoot()->AttachComponent<BoxComponent>();

  comp->transform.scale = Vec3(0.4);

//  GLFWwindow *w = dynamic_cast<ENGH::Platform::OpenGL::GLFWWindow *>(window.get())->nativeWindow;

  input.RegisterAxis(InputKey::KEY_D, "xAxis", -1.0);
  input.RegisterAxis(InputKey::KEY_A, "xAxis", +1.0);

  input.RegisterAxis(InputKey::KEY_E, "yAxis", +1.0);
  input.RegisterAxis(InputKey::KEY_Q, "yAxis", -1.0);

  input.RegisterAxis(InputKey::KEY_W, "zAxis", +1.0);
  input.RegisterAxis(InputKey::KEY_S, "zAxis", -1.0);

  input.RegisterAxis(InputKey::KEY_RIGHT, "yawAxis", 1.0);
  input.RegisterAxis(InputKey::KEY_LEFT, "yawAxis", -1.0);

  input.RegisterAxis(InputKey::KEY_UP, "pitchAxis", -1.0);
  input.RegisterAxis(InputKey::KEY_DOWN, "pitchAxis", +1.0);

  Quat yawRot = Quat::FromAngleAxis(0, VEC3_UP);
  Quat pitchRot = Quat::FromAngleAxis(0, VEC3_RIGHT);

  auto &registrar = input.GetRegistrar();
  registrar.BindAxis("xAxis", [&](double value, double delta) {
    actor->GetPosition().x += value * delta;
//    cam.position += (yawRot * -VEC3_RIGHT) * float(value * delta);
  });
  registrar.BindAxis("yAxis", [&](double value, double delta) {
    actor->GetPosition().y += value * delta;
//    cam.position.y += value * delta;
  });
  registrar.BindAxis("zAxis", [&](double value, double delta) {
    actor->GetPosition().z += value * delta;
//    cam.position += yawRot * ((pitchRot.Inverse() * VEC3_FORWARD) * float(value * delta));
  });
  registrar.BindAxis("yawAxis", [&](double value, double delta) {
    yawRot = yawRot * Quat::FromAngleAxis(value * delta, VEC3_UP);
  });
  registrar.BindAxis("pitchAxis", [&](double value, double delta) {
    pitchRot = pitchRot * Quat::FromAngleAxis(value * delta, VEC3_RIGHT);
  });

  float yaw = 0, pitch = 0;
  world->BeginPlay();
  window->Loop([&](double delta, double total) {
    renderer->Clear(0.2f, 0.2f, 0.2f, 1.0f);
    input.UpdateInputs();
    world->Tick(delta);
    input.Tick(delta);

    cam->rotation = pitchRot * yawRot;

    comp->transform.position.x = sin(total) * 0.2;
    comp->transform.position.y = cos(total) * 0.2;
    comp->transform.rotation = Quat::FromEulerAngles(total * 10 * DEGtoRAD, 0, total * 30 * DEGtoRAD);
    worldRenderer->SetupRender();
    dispatcher.Render();
    context->SwapBuffers();
  });
}
