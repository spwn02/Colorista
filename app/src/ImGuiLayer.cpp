#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>

ImGuiLayer::ImGuiLayer()
  : Layer("ImGui")
{
  
}

void ImGuiLayer::onAttach()
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
  //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
  //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to each other
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  Core::Application& app = Core::Application::get();
  GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getHandle());

  // Setup Platfrom/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 460");

  Log::Info("ImGuiLayer: attached!");
}

void ImGuiLayer::onDetach()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::onEvent(Events::Event& event)
{

}

void ImGuiLayer::onUpdate(float ts)
{

}

void ImGuiLayer::onRender()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGuiIO& io = ImGui::GetIO();
  Core::Application& app = Core::Application::get();
  io.DisplaySize = ImVec2(app.getWindow().getFramebufferSize().x, app.getWindow().getFramebufferSize().y);

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}