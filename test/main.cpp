#include <iostream>
#include <core/math.hpp>
#include <eobject/actor.hpp>
#include <eobject/world/world.hpp>
#include <eobject/component/box_component.hpp>
#include <eobject/component/sphere_component.hpp>
#include <input/input_handler.hpp>
#include <platform/window.hpp>
#include <platform/engh.hpp>

#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/RenderableManager.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
#include <filament/Viewport.h>

#include <utils/EntityManager.h>
#include <math/vec3.h>

#include <array>

#include <generated/resources/resources.h>

/*#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "imgui_adapter.hpp"*/

using ENGH::Logger;
using ENGH::EObject::Actor;
using ENGH::EObject::Comps::BoxComponent;
using ENGH::EObject::Comps::SphereComponent;
using ENGH::EObject::Comps::Component;
using ENGH::EObject::World::World;
using ENGH::Input::InputKey;
using ENGH::Platform::Window;
using ENGH::Render::WorldRenderer;

using namespace filament;
using namespace utils;

using namespace ENGH::Math;

struct Vertex {
  math::float2 position;
  uint32_t     color;
};

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

  auto engh = new ENGH::Platform::ECore();

  auto window = engh->CreateWindow({
                                       true,
                                       "ASD",
                                       800, 600
                                   });
  engh->Setup(filament::backend::Backend::DEFAULT);
  window->Init();

  engh->GetRenderer().setClearOptions({
                                          {0.0f, 0.204f, 0.4f, 1.0f},
                                          true,
                                          true,
                                      });

  /*ImGuiAdapter imGuiAdapter(static_cast<GLFWwindow *>(window->GetNativeHandler()));
  imGuiAdapter.Setup(false);*/

  /*PerspectiveCamera *cam = new PerspectiveCamera();
  cam->fov   = 80 * DEGtoRAD;
  cam->znear = 0.1;
  cam->zfar  = 1000;*/
  /*window->SetResizeCallback([&cam](double width, double height) {
    cam->aspect = width / height;
  });*/

  Engine *engine = engh->GetEngine();

  Scene *scene = engine->createScene();

  auto *material = Material::Builder()
      .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
      .build(*engine);

  static const Vertex TRIANGLE_VERTICES[3] = {
      {{1, 0}, 0xffff0000u},
      {{cos(M_PI * 2 / 3), sin(M_PI * 2 / 3)}, 0xff00ff00u},
      {{cos(M_PI * 4 / 3), sin(M_PI * 4 / 3)}, 0xff0000ffu},
  };

  static constexpr uint16_t TRIANGLE_INDICES[3] = {0, 1, 2};

  auto *vb = VertexBuffer::Builder()
      .vertexCount(3)
      .bufferCount(1)
      .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT2, 0, 12)
      .attribute(VertexAttribute::COLOR, 0, VertexBuffer::AttributeType::UBYTE4, 8, 12)
      .normalized(VertexAttribute::COLOR)
      .build(*engine);
  vb->setBufferAt(*engine, 0, VertexBuffer::BufferDescriptor(TRIANGLE_VERTICES, 36, nullptr));
  auto *ib = IndexBuffer::Builder()
      .indexCount(3)
      .bufferType(IndexBuffer::IndexType::USHORT)
      .build(*engine);
  ib->setBuffer(*engine, IndexBuffer::BufferDescriptor(TRIANGLE_INDICES, 6, nullptr));

  Entity quad = EntityManager::get().create();
// build a quad
  RenderableManager::Builder(1)
      .boundingBox({{-1, -1, -1}, {1, 1, 1}})
      .material(0, material->getDefaultInstance())
      .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vb, ib, 0, 3)
      .culling(false)
      .receiveShadows(false)
      .castShadows(false)
      .build(*engine, quad);
  scene->addEntity(quad);

  Camera *cam = engine->createCamera(EntityManager::get().create());

  View *view = engine->createView();
  {
    const auto[w, h] = window->GetSize();
    view->setViewport({0, 0, static_cast<uint32>(w), static_cast<uint32>(h)});
    view->setVisibleLayers(0x4, 0x4);
    view->setPostProcessingEnabled(false);
    view->setScene(scene);
    view->setCamera(cam);
  }

  window->SelectView(view);

  auto input = ENGH::Input::InputHandler(window->GetInputProvider());

  /*auto context  = window->GetContext();
  auto renderer = context->GetRenderer();

  auto world             = new World();
  auto worldRenderer     = new WorldRenderer(world, context);
  auto dispatcher        = worldRenderer->GetDispatcher();

  SphereComponent *head;
  auto            *actor = world->SpawnActor<Actor>();*/
  /*{
    BoxComponent *comp = actor->GetRoot()->AttachComponent<BoxComponent>();
    comp->transform.scale = Vec3(0.4);
    {
      head = comp->AttachComponent<SphereComponent>();
      head->transform.position = {0.0f, 1.6f, 0.0f};
      head->transform.scale    = Vec3(0.6);
    }
  }*/

  {
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
  }

  Quat yawRot   = Quat::FromAngleAxis(0, VEC3_UP);
  Quat pitchRot = Quat::FromAngleAxis(0, VEC3_RIGHT);

  double x = 0.0;

  {
    auto &registrar = input.GetRegistrar();
    registrar.BindAxis("xAxis", [&](double value, double delta) {
//    cam->position += (yawRot * -VEC3_RIGHT) * float(value * delta);
      x += value * delta;
    });
    registrar.BindAxis("yAxis", [&](double value, double delta) {
//    cam->position.y += value * delta;
    });
    registrar.BindAxis("zAxis", [&](double value, double delta) {
//    cam->position += yawRot * ((pitchRot.Inverse() * VEC3_FORWARD) * float(value * delta));
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
      last             = pressed;
    });
  }

//  world->BeginPlay();

  std::array<float, 60> fps{0};
  std::array<float, 60> frameTime{0};
  double                nextSec = 0;

  constexpr auto last = [](auto &v) constexpr -> auto & { return v[v.size() - 1]; };

  /*window->SetUpdateCallback([&](double delta, double total) {
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

  auto screenFb = context->GetScreenFrameBuffer();

  auto fb = context->CreateFrameBuffer(
      static_cast<FrameBuffer::BufferType>(FrameBuffer::BufferType::COLOR | FrameBuffer::BufferType::DEPTH), 0.0f, 0.0f
  );

  window->SetRenderCallback([&]() {

    fb->Bind();
    renderer->Clear(0.2f, 0.2f, 0.2f, 1.0f);
    worldRenderer->Render();

    screenFb->Bind();
    imGuiAdapter.Begin();
    ImGuiID     dockSpace = ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_AutoHideTabBar);
    static bool first     = true;
    if (first) {
      first = false;
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
          fb->Resize(static_cast<float>(w), static_cast<float>(h));
          cam->aspect = s.x / s.y;
        }

        ImGui::Image(
            reinterpret_cast<ImTextureID>(fb->GetColorTextureID()),
            {
                static_cast<float>(fb->GetWidth()),
                static_cast<float>(fb->GetHeight())
            },
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
  });*/

  window->renderCallback = [&](double delta, double time) {
    input.UpdateInputs();
    input.Tick(delta);
    constexpr float ZOOM   = 1.5f;
    const uint32_t  w      = view->getViewport().width;
    const uint32_t  h      = view->getViewport().height;
    const float     aspect = (float) w / h;
    cam->setProjection(Camera::Projection::ORTHO,
                       -aspect * ZOOM, aspect * ZOOM,
                       -ZOOM, ZOOM, 0, 1);
    auto &tcm = engine->getTransformManager();
    tcm.setTransform(
        tcm.getInstance(quad),
        math::mat4f::translation<float>({-x, 0.0f, 0.0f}) * filament::math::mat4f::rotation(time, filament::math::float3{0.0f, 0.0f, 0.1f})
    );
  };

  window->StartLoop();
//  imGuiAdapter.Shutdown();

}