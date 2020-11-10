#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>

#include <core/math.hpp>
#include <eobject/actor.hpp>
#include <eobject/world/world.hpp>
#include <eobject/component/box_component.hpp>
#include <eobject/component/sphere_component.hpp>
#include <eobject/component/static_mesh_component.hpp>
#include <input/input_handler.hpp>
#include <render/camera/perspective_camera.hpp>
#include <render/world_renderer.hpp>
#include <platform/window.hpp>

#include <platform/opengl/glfw_window.hpp>

#include <util/file/model/obj.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "imgui_adapter.hpp"

using ENGH::Logger;
using ENGH::EObject::Actor;
using ENGH::EObject::Comps::BoxComponent;
using ENGH::EObject::Comps::SphereComponent;
using ENGH::EObject::Comps::StaticMeshComponent;
using ENGH::EObject::Comps::Component;
using ENGH::EObject::World::World;
using ENGH::Input::InputKey;
using ENGH::Platform::Render::BufferDataTypes;
using ENGH::Platform::Render::FrameBuffer;
using ENGH::Platform::Render::RenderLibrary;
using ENGH::Platform::Window;
using ENGH::Platform::OpenGL::GLFWWindow;
using ENGH::Render::Camera::PerspectiveCamera;
using ENGH::Render::WorldRenderer;

using namespace ENGH::Math;

/*bool logInit = false;
void *operator new(size_t size) {
  void* ptr = malloc(size);
  if(logInit) {
    ENGH_CORE_FINE("Allocating ", size, " bytes at ", static_cast<long>((std::uintptr_t)ptr));
  }
  return ptr;
}

void operator delete(void *ptr, size_t size) {
  if(logInit) {
    ENGH_CORE_FINE("Freeing at ", size, "bytes at ", static_cast<long>((std::uintptr_t)ptr));
  }
  return free(ptr);
}*/

int main() {
  Logger::getCoreLogger().SetLevel(Logger::Level::FINER);
//  logInit = true;
  ENGH_INFO("Test application");

  auto window = Window::CreateNewWindow(
      {
          "ASD",
          800, 600
      },
      RenderLibrary::OPENGL
  );
  window->Init();
  ImGuiAdapter imGuiAdapter(dynamic_cast<GLFWWindow *>(window.get())->nativeWindow);
  imGuiAdapter.Setup(true);
  bool loadDefaultLayout = !std::filesystem::exists(ImGui::GetIO().IniFilename);

  auto *cam = new PerspectiveCamera();
  cam->fov   = 80 * DEGtoRAD;
  cam->znear = 0.1;
  cam->zfar  = 1000;
  /*window->SetResizeCallback([&cam](double width, double height) {
    cam->aspect = width / height;
  });*/

  auto input = ENGH::Input::InputHandler(window->GetInputProvider());

  auto context  = window->GetContext();

  auto world             = new World();
  auto worldRenderer     = new WorldRenderer(world, context);
//  auto dispatcher       = worldRenderer->GetDispatcher();

  SphereComponent *head;
  auto            *actor = world->SpawnActor<Actor>();
  {
    ENGH::EObject::Data::Model3D model;
    std::ifstream modelFile("models/Handgun_obj.obj");
    bool ok = ENGH::Util::File::Model::parseObj(modelFile, model);
    if(!ok) {
      ENGH_CORE_WARN("Could not load Handgun_obj.obj model");
    }
    auto *comp = actor->GetRoot()->AttachComponent<StaticMeshComponent>(model);
    comp->transform.scale = Vec3(0.4);
    {
//      head = comp->AttachComponent<SphereComponent>();
//      head->transform.position = {0.0f, 1.6f, 0.0f};
//      head->transform.scale    = Vec3(0.6);
    }
  }

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

  input.RegisterAction(InputKey::KEY_SPACE, "add");

  Quat yawRot   = Quat::FromAngleAxis(0, VEC3_UP);
  Quat pitchRot = Quat::FromAngleAxis(0, VEC3_RIGHT);

  auto &registrar               = input.GetRegistrar();
  registrar.BindAxis("xAxis", [&](double value, double delta) {
//    actor->GetPosition().x += value * delta;
    cam->position += (yawRot * -VEC3_RIGHT) * float(value * delta);
  });
  registrar.BindAxis("yAxis", [&](double value, double delta) {
//    actor->GetPosition().y += value * delta;
    cam->position.y += value * delta;
  });
  registrar.BindAxis("zAxis", [&](double value, double delta) {
//    actor->GetPosition().z += value * delta;
    cam->position += yawRot * ((pitchRot.Inverse() * VEC3_FORWARD) * float(value * delta));
  });
  registrar.BindAxis("yawAxis", [&](double value, double delta) {
    yawRot = yawRot * Quat::FromAngleAxis(value * delta, VEC3_UP);
  });
  registrar.BindAxis("pitchAxis", [&](double value, double delta) {
    pitchRot = pitchRot * Quat::FromAngleAxis(value * delta, VEC3_RIGHT);
  });
  registrar.BindAction("add", [&](bool pressed, double delta) {
    static bool last = false;
    if (pressed && !last) {
      /*head = head->AttachComponent<SphereComponent>();
      head->transform.position = {0.0f, 1.6f, 0.0f};
      head->transform.scale    = Vec3(0.6f);
      auto &transform          = actor->GetTransform();
      transform.position[1] -= transform.scale.y * 1.45f;
      transform.scale *= 1.3f;*/
    }
    last = pressed;
  });

  world->BeginPlay();

  std::array<float, 60> fps{0};
  std::array<float, 60> frameTime{0};
  double                nextSec = 0;

  constexpr auto last = [](auto &v) constexpr -> auto & { return v[v.size() - 1]; };

  window->SetUpdateCallback([&](double delta, double total) {
    input.UpdateInputs();
    world->Tick(delta);
    input.Tick(delta);

    if (total >= nextSec) {
      nextSec = total += 1;
      for (int i    = 1; i < fps.size(); i++) {
        fps[i - 1] = fps[i];
      }
      for (int i    = 1; i < frameTime.size(); i++) {
        frameTime[i - 1] = frameTime[i];
      }
      double   time = window->GetFrameTime();
      last(frameTime) = time * 1000;
      last(fps)       = time < 0.0001 ? 0.0 : 1 / time;
    }

    cam->rotation = pitchRot * yawRot;

    auto &transform = actor->GetTransform();
    transform.rotation = Quat::FromEulerAngles(0, total * 20 * DEGtoRAD, 0);
//    transform.position.x = sin(total) * 0.2;
//    transform.position.y = cos(total) * 0.2;
//    transform.rotation   = Quat::FromEulerAngles(total * 10 * DEGtoRAD, 0, total * 30 * DEGtoRAD);
  });

  window->SetSetupRenderCallback([&]() {
    worldRenderer->SetupRender(cam);
  });

  auto fb = context->CreateFrameBuffer(
      static_cast<FrameBuffer::BufferType>(FrameBuffer::BufferType::COLOR | FrameBuffer::BufferType::DEPTH), 0, 0
  );

  window->SetRenderCallback([&]() {

    fb->Bind();
    worldRenderer->Render();

    context->GetScreenFrameBuffer()->Bind();
    imGuiAdapter.Begin();
    ImGuiID     dockSpace = ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_AutoHideTabBar);
    if (loadDefaultLayout) {
      loadDefaultLayout = false;
      ImGui::DockBuilderRemoveNode(dockSpace);
      ImGui::DockBuilderAddNode(dockSpace, ImGuiDockNodeFlags_DockSpace);
      const auto[width, height] = window->GetSize();
      ImGui::DockBuilderSetNodeSize(dockSpace, {static_cast<float>(width), static_cast<float>(height)});

      ImGuiID dockRight, dockLeft, dockLeftDown, dockLeftUp;
      dockLeft   = ImGui::DockBuilderSplitNode(dockSpace, ImGuiDir_Left, 0.30f, NULL, &dockRight);
      dockLeftUp = ImGui::DockBuilderSplitNode(dockLeft, ImGuiDir_Up, 0.50f, NULL, &dockLeftDown);

      ImGui::DockBuilderDockWindow("Scene", dockRight);
      ImGui::DockBuilderDockWindow("Stats", dockLeftUp);
      ImGui::DockBuilderDockWindow("Ball", dockLeftDown);

      imGuiAdapter.SetMainDock(ImHashStr("Scene"));
    }
    {
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
      if (ImGui::Begin("Scene")) {
        static float w = 0, h = 0;

        auto s = ImGui::GetContentRegionAvail();
        if (w != s.x || h != s.y) {
          w = s.x;
          h = s.y;
          fb->Resize(static_cast<int64>(w * 4), static_cast<int64>(h * 4));
          cam->aspect = s.x / s.y;
        }

        ImGui::Image(
            reinterpret_cast<ImTextureID>(fb->GetColorTextureID()),
            {w, h},
            {0, 1},
            {1, 0}
        );
      }
      ImGui::End();
      ImGui::PopStyleVar();

      if (ImGui::Begin("Stats")) {
        auto labelPlot = [&last](auto text, auto arr, auto t2) {
          ImGui::Text("%s: %02f", text, last(arr));
          ImGui::PlotLines(t2, arr.data(), arr.size());
        };
        labelPlot("FPS", fps, "");
        labelPlot("FrameTime", frameTime, "ms");
      }
      ImGui::End();

      if (ImGui::Begin("Ball")) {
//        ImGui::SliderInt("Lat", reinterpret_cast<int *>(&head->latCount), 1, 100);
//        ImGui::SliderInt("Lng", reinterpret_cast<int *>(&head->longCount), 1, 100);
      }
      ImGui::End();
    }
    imGuiAdapter.End();
    context->SwapBuffers();
  });

  window->StartLoop();
  imGuiAdapter.Shutdown();

}