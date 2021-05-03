#pragma once

#include <editor/panel/PanelBase.hpp>

#include <core/data_types.hpp>

#include <set>

namespace filament {
class Engine;
class View;
}

namespace utils {
class Path;
}

namespace ENGH::Input {
class InputProvider;
}

namespace filagui {
class ImGuiHelper;
}

namespace ENGH::Editor {

class ImGuiAdapter {
  ENGHEditor           *editor;
  filament::View       *view;
  filagui::ImGuiHelper *filagui;

  ENGH::Input::InputProvider *provider;
public:
  ImGuiAdapter(ENGHEditor *editor, filament::View *view, ENGH::Input::InputProvider *provider);

  ~ImGuiAdapter();

  void render(float delta, uint32 width, uint32 height, const std::set<PanelBase *> &panels);
};

}
