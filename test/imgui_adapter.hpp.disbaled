#pragma once

#include <imgui/imgui.h>

class ImGuiAdapter {
  struct GLFWwindow* glfwWindow;
public:
  ImGuiAdapter(struct GLFWwindow* window);

  void Setup(bool savelayout);

  void SetMainDock(ImGuiID id);

  void Shutdown();

  void Begin();

  void End();
};
