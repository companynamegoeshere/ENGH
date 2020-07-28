#pragma once

class ImGuiAdapter {
  class GLFWwindow* glfwWindow;
public:
  ImGuiAdapter(class GLFWwindow* window);

  void Setup();

  void Shutdown();

  void Begin();

  void End();
};
