#pragma once

#include <editor/panel/PanelBase.hpp>

namespace ENGH::Editor {

class WorldViewer : public PanelBase {
public:
  WorldViewer();

  void onGUI(ENGHEditor *editor, filament::View*) override;
};

}