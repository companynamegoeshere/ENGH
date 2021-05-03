#include <editor/panel/WorldViewer.hpp>

#include <core/log.hpp>

#include <imgui.h>

namespace ENGH::Editor {

WorldViewer::WorldViewer() {

}

void WorldViewer::onGUI(ENGHEditor *editor, filament::View*) {
  ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
  ImGui::Begin("Test");
  {
    if(ImGui::Button("Test")) {
      ENGH_INFO("Pressed");
    }
  }
  ImGui::End();
  ImGui::ShowDemoWindow(nullptr);
}

}
