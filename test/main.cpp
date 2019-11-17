#include <iostream>
#include <platform/window.hpp>
#include <eobject/actor.hpp>
#include <eobject/world.hpp>
#include <eobject/component/box_component.hpp>
#include <render/camera/perspective_camera.hpp>
#include <render/world_renderer.hpp>
#include <core/math.hpp>
#include <platform/opengl/glfw_window.hpp>
#include <GLFW/glfw3.h>

using ENGH::Logger;
using ENGH::EObject::Actor;
using ENGH::EObject::Comps::BoxComponent;
using ENGH::EObject::Comps::Component;
using ENGH::EObject::World;
using ENGH::Platform::Render::BufferDataTypes;
using ENGH::Platform::Render::RenderLibrary;
using ENGH::Platform::Window;
using ENGH::Render::Camera::PerspectiveCamera;
using ENGH::Render::WorldRenderer;

using namespace ENGH::Math;

int main() {
  Logger::getCoreLogger().SetLevel(Logger::Level::ALL);
  ENGH_INFO("Test application");

  WorldRenderer *worldRenderer = nullptr;
  PerspectiveCamera cam;
  cam.fov = 80 * DEGtoRAD;
  cam.znear = 0.1;
  cam.zfar = 1000;

  auto window = Window::CreateWindow(
      {
          "ASD",
          800, 600
      },
      RenderLibrary::OPENGL
  );
  window->SetResizeCallback([&](double width, double height) {
    cam.aspect = width / height;
    cam.UpdateProjectionMatrix();
    if (worldRenderer != nullptr) {
      worldRenderer->GetDispatcher().SetProjection(cam.GetProjection());
    }
  });
  window->Init();

  auto context = window->GetContext();
  auto renderer = context->GetRenderer();

  auto world = new World();
  worldRenderer = new WorldRenderer(world, context);
  auto &dispatcher = worldRenderer->GetDispatcher();
  dispatcher.SetProjection(cam.GetProjection());

  auto *actor = world->SpawnActor<Actor>();

  BoxComponent *comp = new BoxComponent();
  actor->GetRoot()->children += comp;

  comp->transform.scale = Vec3(0.4);

  GLFWwindow *w = dynamic_cast<ENGH::Platform::OpenGL::GLFWWindow *>(window.get())->nativeWindow;

  float yaw = 0, pitch = 0;
  world->BeginPlay();
  window->Loop([&](double delta, double total) {
    renderer->Clear(0.2f, 0.2f, 0.2f, 1.0f);
    world->Tick(delta);
    float xAxis = -((glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS));
    float yAxis = (glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS);
    float zAxis = (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS);

    pitch -= ((glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS)) * delta;
    yaw += ((glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)) * delta;
    Quat yawRot = Quat::FromAngleAxis(yaw, VEC3_UP);
    Quat pitchRot = Quat::FromAngleAxis(pitch, VEC3_RIGHT);
    Quat finalRot = pitchRot * yawRot;
    cam.position += (yawRot * -VEC3_RIGHT) * float(xAxis * delta) + yawRot * ((pitchRot.Inverse() * VEC3_FORWARD) * float(zAxis * delta))
        + Vec3(0, yAxis * delta, 0);
    cam.rotation = finalRot;

    comp->transform.position.x = sin(total) * 0.2;
    comp->transform.position.y = cos(total) * 0.2;
    comp->transform.rotation = Quat::FromEulerAngles(total * 10 * DEGtoRAD, 0, total * 30 * DEGtoRAD);
    worldRenderer->SetupRender();
    dispatcher.SetView(cam.GetView());
    dispatcher.Render();
    context->SwapBuffers();
  });
}
