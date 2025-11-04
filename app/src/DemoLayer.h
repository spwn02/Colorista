#pragma once

#include "Core.h"

class DemoLayer : public Core::Layer
{
public:
  DemoLayer();
  virtual ~DemoLayer();

  void onAttach() override;
  void onDetach() override;
  void onEvent(Events::Event& event) override;

  void onUpdate(float ts) override;
  void onRender() override;
private:
  std::shared_ptr<Renderer::GraphicsShader> m_shader;
  std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
  std::shared_ptr<Renderer::Renderer> m_renderer;
};