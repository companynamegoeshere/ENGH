#include <editor/ImGuiAdapter.hpp>
#include <editor/Editor.hpp>

#include <platform/engh.hpp>
#include <input/input_provider.hpp>

#include <filament/Engine.h>
#include <filament/View.h>
#include <filament/Viewport.h>

#include <imgui.h>
#include <filagui/ImGuiHelper.h>

using ENGH::Input::InputKey;

#ifndef RELATIVE_ASSET_PATH
#define RELATIVE_ASSET_PATH "."
#endif

static const utils::Path &getRootAssetsPath() {
  static const utils::Path root = utils::Path::getCurrentExecutable().getParent() + RELATIVE_ASSET_PATH;
  return root;
}

static void setupImGuiKeys(ImGuiIO &io) {
  using ENGH::Input::InputKey;
  io.KeyMap[ImGuiKey_Tab]         = InputKey::KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow]   = InputKey::KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow]  = InputKey::KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow]     = InputKey::KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow]   = InputKey::KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp]      = InputKey::KEY_PG_UP;
  io.KeyMap[ImGuiKey_PageDown]    = InputKey::KEY_PG_DOWN;
  io.KeyMap[ImGuiKey_Home]        = InputKey::KEY_HOME;
  io.KeyMap[ImGuiKey_End]         = InputKey::KEY_END;
  io.KeyMap[ImGuiKey_Insert]      = InputKey::KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete]      = InputKey::KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace]   = InputKey::KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space]       = InputKey::KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter]       = InputKey::KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape]      = InputKey::KEY_ESC;
  io.KeyMap[ImGuiKey_KeyPadEnter] = InputKey::KEY_NP_ENTER;
  io.KeyMap[ImGuiKey_A]           = InputKey::KEY_A;
  io.KeyMap[ImGuiKey_C]           = InputKey::KEY_C;
  io.KeyMap[ImGuiKey_V]           = InputKey::KEY_V;
  io.KeyMap[ImGuiKey_X]           = InputKey::KEY_X;
  io.KeyMap[ImGuiKey_Y]           = InputKey::KEY_Y;
  io.KeyMap[ImGuiKey_Z]           = InputKey::KEY_Z;
}

namespace ENGH::Editor {

//TODO Scroll

ImGuiAdapter::ImGuiAdapter(
    ENGHEditor *editor,
    filament::View *view,
    ENGH::Input::InputProvider *provider) :
    editor(editor), view(view), provider(provider) {

  this->filagui = new filagui::ImGuiHelper(editor->GetCore()->GetEngine(), view, getRootAssetsPath() + "assets/fonts/Roboto-Medium.ttf");

  auto &io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  setupImGuiKeys(io);

  provider->RegisterKeyCallback([&io](InputKey key, bool pressed) {
    io.KeysDown[key] = pressed;
    if (key == InputKey::KEY_L_CTRL || key == Input::KEY_R_CTRL) {
      io.KeyCtrl = pressed;
    }
    if (key == InputKey::KEY_L_SHIFT || key == Input::KEY_R_SHIFT) {
      io.KeyShift = pressed;
    }
    if (key == InputKey::KEY_L_ALT || key == Input::KEY_R_ALT) {
      io.KeyAlt = pressed;
    }
  });
  provider->RegisterCharCallback([&io](unsigned int c) {
    io.AddInputCharacter(c);
  });
  provider->RegisterCursorCallback([&io](double mouseX, double mouseY) {
    io.MousePos = {(float) mouseX, (float) mouseY};
  });
}

ImGuiAdapter::~ImGuiAdapter() {
  delete this->filagui;
  // TODO Remove key/mouse callbacks
}

void ImGuiAdapter::render(
    float delta, uint32 width, uint32 height,
    const std::set<PanelBase *> &panels) {

  if (provider->IsFocused()) {
    auto &io = ImGui::GetIO();
    for(int i = 0; i < 5; i++) {
      io.MouseDown[i] = provider->IsPressed(Input::MOUSE_BUTTONS[i]);
    }
    if (io.WantSetMousePos) {
      auto pos = io.MousePos;
      provider->SetCursorPos(pos.x, pos.y);
    }
  }

  view->setViewport({0, 0, static_cast<uint32>(width), static_cast<uint32>(height)});
  this->filagui->setDisplaySize((int) width, (int) height);
  this->filagui->render((float) delta, [this, &panels](auto *engine, auto *view) {
    for (const auto &item : panels) {
      item->onGUI(editor, view);
    }
  });
}

}
