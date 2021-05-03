#pragma once

namespace filament {
class View;
}

namespace ENGH::Editor {

class ENGHEditor;

class PanelBase {
public:
//  virtual void preRender(ENGHEditor *editor) {}

  virtual void onGUI(ENGHEditor *editor, filament::View*) = 0;

//  virtual void postRender(ENGHEditor *editor) {}

};

}