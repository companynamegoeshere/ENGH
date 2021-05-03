#include <editor/Editor.hpp>

#include <editor/ImGuiAdapter.hpp>
#include <editor/panel/PanelBase.hpp>
#include <editor/panel/WorldViewer.hpp.>

#include <platform/engh.hpp>
#include <platform/window.hpp>
#include <input/input_handler.hpp>

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

using namespace ENGH::Platform;

namespace ENGH::Editor {

class FEditor {
public:
  ENGHEditor *shared;
  ECore      *core;
  Window     *window;

  ENGH::Input::InputHandler *input;

  filament::View *uiView;
  ImGuiAdapter   *imGuiAdapter;

  std::set<PanelBase *> panels;

  FEditor(ENGHEditor *editor) : shared(editor), core(new ECore) {}

  void run();
private:

  void renderCallback(double delta, double time);
};

ENGHEditor::ENGHEditor() : editor(new FEditor(this)) {
  core = editor->core;
}

void ENGHEditor::run() {
  editor->run();
}

void FEditor::run() {
#ifdef ENGH_DEBUG
  Logger::getCoreLogger().SetLevel(Logger::Level::FINER);
#else
  Logger::getCoreLogger().SetLevel(Logger::Level::INFO);
#endif

  ENGH_INFO("Starting editor");
  window = core->CreateWindow(
      {
          true,
          "ENGH Editor",
          1500, 800
      }
  );
  core->Setup();
  window->CreateWindow();

  auto *filament = core->GetEngine();
  auto &renderer = core->GetRenderer();
  renderer.setClearOptions(
      {
          {0.0f, 0.204f, 0.4f, 1.0f},
//          {0.2f, 0.2f, 0.2f, 1.0f},
          true, true
      }
  );
  auto *inputProvider = window->GetInputProvider();

  input = new ENGH::Input::InputHandler(inputProvider);

  uiView       = filament->createView();
  imGuiAdapter = new ImGuiAdapter(shared, uiView, inputProvider);

  panels.insert(new WorldViewer);

  window->SelectView(uiView);
  window->renderCallback = [this](auto v1, auto v2) { this->renderCallback(v1, v2); };
  window->StartLoop();

}

void FEditor::renderCallback(double delta, double time) {
  input->UpdateInputs();
  input->Tick(delta);

  const auto[width, height] = window->GetSize();
  imGuiAdapter->render((float) delta, width, height, panels);
}

}
