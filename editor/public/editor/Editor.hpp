#pragma once

namespace ENGH::Platform {
class ECore;
}

namespace ENGH::Editor {

class FEditor;

class ENGHEditor {
  Platform::ECore *core;
  FEditor         *editor;
public:
  ENGHEditor();

  void run();

  inline Platform::ECore *GetCore() { return core; }
};

}