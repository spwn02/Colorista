#pragma once

#include "Core.h"
#include "EditorState.h"

#include "imgui.h"

class ImGuiLayer : public Core::Layer
{
public:
  ImGuiLayer(EditorState& state);
  ~ImGuiLayer() {};

  void onAttach() override;
  void onDetach() override;
  void onEvent(Events::Event& event) override;

  virtual void onUpdate(float ts) override;
  virtual void onRender() override;

private:
  void begin();
  void end();

  void viewport();
  void menuBar();
  void toolsPanel();
  void propertiesPanel();
  void statsWindow();

  bool brushIcon(const char* id, float size, ImU32 col, BrushType shape);

  EditorState& m_state;
};