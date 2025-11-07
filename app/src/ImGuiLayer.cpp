#include "imguipch.h"

#include "ImGuiLayer.h"

ImGuiLayer::ImGuiLayer(EditorState& state)
  : Layer("ImGui"), m_state(state)
{
  
}

void ImGuiLayer::onAttach()
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
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
    style.WindowRounding = 5.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  Core::Application& app = Core::Application::get();
  GLFWwindow* window = (GLFWwindow*)app.getWindow().getHandle();

  // Setup Platfrom/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 460 core");

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
  ImGuiIO& io = ImGui::GetIO();
  if (io.WantCaptureMouse)
  {
    //Log::Trace("ImGuiLayer: received event!");
    //event.handled = true;
  }
}

void ImGuiLayer::onUpdate(float ts)
{

}

void ImGuiLayer::begin()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ImGuiViewport* mainViewport = ImGui::GetMainViewport();
  ImGui::DockSpaceOverViewport(mainViewport->ID, mainViewport, ImGuiDockNodeFlags_PassthruCentralNode);

  m_state.viewportSize = glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
}

void ImGuiLayer::end()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();

    /*ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
    for (ImGuiViewport* vp : pio.Viewports)
    {
      GLFWwindow* wnd = (GLFWwindow*)vp->PlatformHandle;
      glfwMakeContextCurrent(wnd);

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glViewport(0, 0, (int)vp->Size.x, (int)vp->Size.y);

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }*/

    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void ImGuiLayer::onRender()
{
  begin();
  //ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar |
  //  ImGuiWindowFlags_NoMove |
  //  ImGuiWindowFlags_NoResize |
  //  ImGuiWindowFlags_NoCollapse |
  //  ImGuiWindowFlags_NoTitleBar |
  //  ImGuiWindowFlags_NoSavedSettings;

  ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoSavedSettings;

  viewport();
  menuBar();
  toolsPanel();
  propertiesPanel();
  if (m_state.showStats) statsWindow();

  //ImGui::ShowDemoWindow();

  end();
}

void ImGuiLayer::viewport()
{
  ImGui::Begin("Scene");

  // Panel (cropping) rect in ImGui units
  const ImVec2 content_min = ImGui::GetCursorScreenPos();
  const ImVec2 avail = ImGui::GetContentRegionAvail();
  const ImVec2 content_max = ImVec2(content_min.x + avail.x, content_min.y + avail.y);

  // Canvas size in FRAMEBUFFER pixels (fixed FBO size, e.g. 1920x1080)
  const ImVec2 canvas_px(m_state.canvasSize.x, m_state.canvasSize.y);

  // Convert canvas pixels -> ImGui units using the window's DPI scale
  ImGuiViewport* vp = ImGui::GetWindowViewport();
  const float fb_scale = vp ? vp->DpiScale : 1.0f;
  const ImVec2 canvas_ui(canvas_px.x / fb_scale, canvas_px.y / fb_scale);

  // Place image (top-left or centered), then SNAP to pixel grid
  ImVec2 origin = content_min;
  if (m_state.centerView) {
    origin.x += std::max(0.0f, (avail.x - canvas_ui.x) * 0.5f) + m_state.pan.x;
    origin.y += std::max(0.0f, (avail.y - canvas_ui.y) * 0.5f) + m_state.pan.y;
  }
  else {
    origin.x += m_state.pan.x;
    origin.y += m_state.pan.y;
  }
  auto snap = [](float v, float scale) { return std::floor(v * scale + 0.5f) / scale; };
  origin.x = snap(origin.x, fb_scale);
  origin.y = snap(origin.y, fb_scale);

  // CROP to panel rect (no scaling)
  ImGui::PushClipRect(content_min, content_max, true);
  ImGui::GetWindowDrawList()->AddImage(
    (void*)m_state.texture->getTextureID(),
    origin,
    ImVec2(origin.x + canvas_ui.x, origin.y + canvas_ui.y),
    ImVec2(0, 1), ImVec2(1, 0) // keep full texture, no UV scale
  );
  ImGui::PopClipRect();

  // Hover + mouse→UV mapping in canvas pixels (for accurate brush)
  const ImVec2 mouse = ImGui::GetMousePos();
  float local_x_px = (mouse.x - origin.x) * fb_scale;
  float local_y_px = (mouse.y - origin.y) * fb_scale;

  const bool over_panel = ImGui::IsMouseHoveringRect(content_min, content_max, true);
  const bool over_image = (local_x_px >= 0 && local_y_px >= 0 &&
    local_x_px < canvas_px.x && local_y_px < canvas_px.y);

  m_state.viewportHovered = (over_panel && over_image);

  // UVs in [0..1] (flip V to match AddImage uv)
  float u = canvas_px.x > 0 ? local_x_px / canvas_px.x : 0.0f;
  float v = canvas_px.y > 0 ? 1.0f - (local_y_px / canvas_px.y) : 0.0f;
  m_state.mouseUV = { std::clamp(u, 0.0f, 1.0f), std::clamp(v, 0.0f, 1.0f) };

  // (Optional) show a border of the content area
  ImGui::GetWindowDrawList()->AddRect(content_min, content_max, IM_COL32(255,255,255,255));

  ImGui::End();
}

void ImGuiLayer::menuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Reset", "Ctrl+R"))
      {
        m_state.resetRequested = true;
        Log::Info("Reset!");
      }
      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "Esc"))
      {
        Core::Application::get().shutdown();
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
    {
      ImGui::MenuItem("Stats", nullptr, &m_state.showStats);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Brush"))
    {
      ImGui::TextDisabled("Quick Actions");
      if (ImGui::MenuItem("Size +")) m_state.brushSize += 1.0f;
      if (ImGui::MenuItem("Size -")) m_state.brushSize = std::max(1.0f, m_state.brushSize - 1.0f);
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

void ImGuiLayer::toolsPanel()
{
  ImGui::Begin("Tools");

  /*ImGuiViewport* vp = ImGui::GetWindowViewport();
  float scale = vp ? vp->DpiScale : 1.0f;
  glm::vec2 texSize(m_state.brushIcons.size / scale, m_state.brushIcons.size / scale);

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 1.0f));

  ImVec2 size(32.0f, 32.0f);
  ImVec2 uv0(0.0f, 1.0f);
  ImVec2 uv1(1.0f, 0.0f);
  ImVec4 bgCol(0.2f, 0.2f, 0.2f, 1.0f);
  ImVec4 tintCol(m_state.brushColor.r, m_state.brushColor.g, m_state.brushColor.b, m_state.brushColor.a);
  if (ImGui::ImageButton("Square", m_state.brushIcons.square->getTextureID(), size, uv0, uv1, bgCol, tintCol))
  {
    m_state.brushType = BrushType::Square;
  }
  ImGui::SameLine();

  if (ImGui::ImageButton("Triangle", m_state.brushIcons.triangle->getTextureID(), size, uv0, uv1, bgCol, tintCol))
  {
    m_state.brushType = BrushType::Triangle;
  }
  ImGui::SameLine();

  if (ImGui::ImageButton("TriangleC", m_state.brushIcons.triangle->getTextureID(), size, uv0, uv1, bgCol, tintCol))
  {
    m_state.brushType = BrushType::TriangleC;
  }
  ImGui::SameLine();

  if (ImGui::ImageButton("Circle", m_state.brushIcons.circle->getTextureID(), size, uv0, uv1, bgCol, tintCol))
  {
    m_state.brushType = BrushType::Circle;
  }
  ImGui::SameLine();

  ImGui::PopStyleVar();*/

  const float size = 32.0f / (ImGui::GetWindowViewport()->DpiScale);
  ImU32 tint = IM_COL32(
    (int)(m_state.brushColor.r * 255),
    (int)(m_state.brushColor.g * 255),
    (int)(m_state.brushColor.b * 255),
    (int)(m_state.brushColor.a * 255)
    );

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 4.0f));

  if (brushIcon("Square", size, tint, BrushType::Square)) m_state.brushType = BrushType::Square;
  ImGui::SameLine();
  if (brushIcon("Triangle", size, tint, BrushType::Triangle)) m_state.brushType = BrushType::Triangle;
  ImGui::SameLine();
  if (brushIcon("TriangleC", size, tint, BrushType::TriangleC)) m_state.brushType = BrushType::TriangleC;
  ImGui::SameLine();
  if (brushIcon("Circle", size, tint, BrushType::Circle)) m_state.brushType = BrushType::Circle;

  ImGui::PopStyleVar();

  ImGui::End();
}

void ImGuiLayer::propertiesPanel()
{
  ImGui::Begin("Properties");
  ImGui::SliderFloat("Brush Size", &m_state.brushSize, 1.0f, 128.0f, "%.0f");
  ImGui::ColorEdit4("Brush Color", (float*)&m_state.brushColor, ImGuiColorEditFlags_NoInputs);
  if (ImGui::Button("Reset Canvas")) m_state.resetRequested = true;
  ImGui::End();
}

void ImGuiLayer::statsWindow()
{
  ImGui::Begin("Stats", &m_state.showStats);
  ImGui::Text("Brush: %d", (unsigned int)m_state.brushType);
  ImGui::Text("Brush size: %.1f", m_state.brushSize);
  ImGui::Text("Color: R=%.2f, G=%.2f, B=%.2f, A=%.2f", m_state.brushColor.r, m_state.brushColor.g, m_state.brushColor.b, m_state.brushColor.a);
  ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
  ImGui::End();
}

bool ImGuiLayer::brushIcon(const char* id, float size, ImU32 col, BrushType shape)
{
  ImGui::PushID(id);
  ImVec2 p0 = ImGui::GetCursorScreenPos();
  ImVec2 p1 = ImVec2(p0.x + size, p0.y + size);

  bool pressed = ImGui::InvisibleButton("##brushIcon", ImVec2(size, size));
  ImDrawList* dl = ImGui::GetWindowDrawList();

  // background
  dl->AddRectFilled(p0, p1, IM_COL32(60, 60, 60, 255), 4.0f);

  // icon
  ImVec2 center((p0.x + p1.x) * 0.5f, (p0.y + p1.y) * 0.5f);
  float r = size * 0.35f;
  switch (shape)
  {
  case BrushType::Square:
  {
    float h = r * 0.95f;
    dl->AddRectFilled(ImVec2(center.x - h, center.y - h), ImVec2(center.x + h, center.y + h), col, 0.0f);
    break;
  }
  case BrushType::Triangle:
  {
    ImVec2 a(center.x - r, center.y - r);
    ImVec2 b(center.x - r, center.y + r);
    ImVec2 c(center.x + r, center.y + r);
    dl->AddTriangleFilled(a, b, c, col);
    break;
  }
  case BrushType::TriangleC:
  {
    ImVec2 a(center.x, center.y - r);
    ImVec2 b(center.x - r, center.y + r);
    ImVec2 c(center.x + r, center.y + r);
    dl->AddTriangleFilled(a, b, c, col);
    break;
  }
  case BrushType::Circle:
  {
    dl->AddCircleFilled(center, r, col, 0);
    break;
  }
  }

  if (ImGui::IsItemHovered()) dl->AddRect(p0, p1, IM_COL32(180, 180, 180, 255), 4.0f);
  ImGui::PopID();
  return pressed;
}