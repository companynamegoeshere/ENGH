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

  PerspectiveCamera cam;
  cam.fov = 80 * DEGtoRAD;
  cam.znear = 0.1;
  cam.zfar = 1000;
  cam.aspect = 800.0f / 600.0f; // TODO Get window size
  cam.UpdateProjectionMatrix();
  worldRenderer->GetDispatcher().SetProjection(cam.GetProjection());

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
    float xAxis = (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS);
    float yAxis = (glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS);
    float zAxis = (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS);

    pitch += ((glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS)) * delta;
    yaw += ((glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS) - (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)) * delta;
    cam.position.x += xAxis * delta;
    cam.position.y += yAxis * delta;
    cam.position.z += zAxis * delta;
    cam.rotation = Quat::FromAngleAxis(pitch, VEC3_RIGHT) * Quat::FromAngleAxis(yaw, VEC3_UP);
//    cam.position.z = sin(total * 0.7) * 1.5;
//    cam.position.x = cos(total * 0.7) * -1.5;
    // cam.rotation = Quat::FromMatrix(Mat4::LookAt(VEC3_ZERO, cam.position, VEC3_UP)); //Quat::FromEulerAngles(0, total * 0.7 * HALF_PI / 2, 0);
//    comp->transform.position.x = sin(total) * 0.2;
//    comp->transform.position.y = cos(total) * 0.2;
//    comp->transform.rotation = Quat::FromEulerAngles(total * 10 * DEGtoRAD, 0, total * 30 * DEGtoRAD);
    worldRenderer->SetupRender();
    auto &dispatcher = worldRenderer->GetDispatcher();
    dispatcher.SetView(cam.GetView());
    dispatcher.Render();
    context->SwapBuffers();
  });
}
