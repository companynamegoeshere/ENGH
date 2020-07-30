#pragma once

class ImGuiAdapter {
  struct GLFWwindow* glfwWindow;
public:
  ImGuiAdapter(struct GLFWwindow* window);

  void Setup();

  void Shutdown();

  void Begin();

  void End();
};
