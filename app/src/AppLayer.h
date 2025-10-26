#pragma once

#include "Core.h"

class AppLayer : public Core::Layer
{
public:
  AppLayer();
  virtual ~AppLayer();

  void onAttach() override;
  void onDetach() override;
  void onEvent(Core::Event& event) override;

  void onUpdate(float ts) override;
  void onRender() override;
private:
  uint32_t m_shader = 0;
  uint32_t m_vertexArray = 0;
  uint32_t m_vertexBuffer = 0;
};