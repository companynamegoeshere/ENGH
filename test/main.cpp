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
#include <filament/LightManager.h>
#include <filament/Material.h>
#include <filament/RenderableManager.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
#include <filament/Viewport.h>
#include <math/norm.h>

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
//  uint32_t     color;
  math::short4 tangents;
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
  window->CreateWindow();

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
//      .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
      .package(RESOURCES_AIDEFAULTMAT_DATA, RESOURCES_AIDEFAULTMAT_SIZE)
      .build(*engine);

  auto mi = material->createInstance();
  mi->setParameter("baseColor", RgbType::sRGB, math::float3{1.0f, 0.55f, 0.0f});
  mi->setParameter("metallic", 1.0f);
  mi->setParameter("roughness", 0.4f);
  mi->setParameter("reflectance", 0.5f);

//  const auto up = math::quatf::fromAxisAngle(math::float3{1.0f, 0.0f, 0.0f}, DEGtoRAD * 90.0).xyzw;
  math::short4 up = math::packSnorm16(
      math::mat3f::packTangentFrame({
                                        math::float3{0.0f, 1.0f, 0.0f},
                                        math::float3{1.0f, 0.0f, 0.0f},
                                        math::float3{0.0f, 0.0f, 1.0f}
                                    }).xyzw
  );

  static const Vertex TRIANGLE_VERTICES[3] = {
      /*{{1, 0}, 0xffff0000u},
      {{cos(M_PI * 2 / 3), sin(M_PI * 2 / 3)}, 0xff00ff00u},
      {{cos(M_PI * 4 / 3), sin(M_PI * 4 / 3)}, 0xff0000ffu},*/
      {{1, 0}, up},
      {{cos(PI * 2 / 3), sin(PI * 2 / 3)}, up},
      {{cos(PI * 4 / 3), sin(PI * 4 / 3)}, up}
  };

  static constexpr uint16_t TRIANGLE_INDICES[3] = {0, 1, 2};

  auto *vb = VertexBuffer::Builder()
      .vertexCount(3)
      .bufferCount(1)
      .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT2, offsetof(Vertex, position), sizeof(Vertex))
      .attribute(VertexAttribute::TANGENTS, 0, VertexBuffer::AttributeType::SHORT4, offsetof(Vertex, tangents), sizeof(Vertex))
      .normalized(VertexAttribute::TANGENTS)
//      .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT2, 0, 12)
//      .attribute(VertexAttribute::COLOR, 0, VertexBuffer::AttributeType::UBYTE4, 8, 12)
//      .normalized(VertexAttribute::COLOR)
      .build(*engine);
  vb->setBufferAt(*engine, 0, VertexBuffer::BufferDescriptor(TRIANGLE_VERTICES, sizeof(TRIANGLE_VERTICES), nullptr));
  auto *ib = IndexBuffer::Builder()
      .indexCount(3)
      .bufferType(IndexBuffer::IndexType::USHORT)
      .build(*engine);
  ib->setBuffer(*engine, IndexBuffer::BufferDescriptor(TRIANGLE_INDICES, sizeof(TRIANGLE_INDICES), nullptr));

  Entity quad = EntityManager::get().create();
// build a quad
  RenderableManager::Builder(1)
      .boundingBox({{-1, -1, -1}, {1, 1, 1}})
//      .material(0, material->getDefaultInstance())
      .material(0, mi)
      .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vb, ib, 0, 3)
      .culling(false)
      .receiveShadows(false)
      .castShadows(false)
      .build(*engine, quad);
  scene->addEntity(quad);

  auto light = EntityManager::get().create();
  LightManager::Builder(LightManager::Type::DIRECTIONAL)
      .color(Color::toLinear<ACCURATE>({0.98f, 0.92f, 0.89f}))
      .intensity(110000)
      .direction({0.6, -1, -0.8})
      .build(*engine, light);
  scene->addEntity(light);

  auto   camEnt = EntityManager::get().create();
  Camera *cam   = engine->createCamera(camEnt);

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

//  Quat yawRot   = Quat::FromAngleAxis(0, VEC3_UP);
//  Quat pitchRot = Quat::FromAngleAxis(0, VEC3_RIGHT);
  math::mat4f rot;

  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  {
    auto &registrar = input.GetRegistrar();
    registrar.BindAxis("xAxis", [&](double value, double delta) {
      x += value * delta;
    });
    registrar.BindAxis("yAxis", [&](double value, double delta) {
      z += value * delta;
    });
    registrar.BindAxis("zAxis", [&](double value, double delta) {
      y += value * delta;
    });
    registrar.BindAxis("yawAxis", [&](double value, double delta) {
//      yawRot = yawRot * Quat::FromAngleAxis(value * delta, VEC3_UP);
      rot *= math::mat4f::rotation(value * delta, math::float3{0.0f, 1.0f, 0.0f});
    });
    registrar.BindAxis("pitchAxis", [&](double value, double delta) {
//      pitchRot = pitchRot * Quat::FromAngleAxis(value * delta, VEC3_RIGHT);
      rot *= math::mat4f::rotation(value * delta, math::float3{1.0f, 0.0f, 0.0f});
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

  auto &tcm = engine->getTransformManager();

  auto callback = [&](double delta, double time) {
    input.UpdateInputs();
    input.Tick(delta);
    constexpr float ZOOM   = 1.5f;
    const uint32_t  w      = view->getViewport().width;
    const uint32_t  h      = view->getViewport().height;
    const float     aspect = (float) w / h;
    /*cam->setProjection(Camera::Projection::ORTHO,
                       -aspect * ZOOM, aspect * ZOOM,
                       -ZOOM, ZOOM, 0, 1);*/
    cam->setProjection(90.0, aspect, 0.1, 10000.0f);
    cam->lookAt({0.0f, 0.0f, 2.0f}, {0.0f, 0.0f, 0.0f});
//    auto rotData = (yawRot * pitchRot).ToMatrix4().Transpose();
    tcm.setTransform(
        tcm.getInstance(quad),
        math::mat4f::translation<float>({-x, y, z}) * rot
            /** *((math::mat4f*)(&rotData.data_))*/ /*filament::math::mat4f::rotation(time, filament::math::float3{0.0f, 0.0f, 0.1f})*/
    );
  };

  window->renderCallback = callback;

  window->StartLoop();
//  imGuiAdapter.Shutdown();

}