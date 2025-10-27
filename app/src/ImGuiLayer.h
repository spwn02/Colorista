#pragma once

#include "Core.h"

class ImGuiLayer : public Core::Layer
{
public:
  ImGuiLayer();
  ~ImGuiLayer() {}

  void onAttach() override;
  void onDetach() override;
  void onEvent(Events::Event& event) override;

  virtual void onUpdate(float ts) override;
  virtual void onRender() override;
};