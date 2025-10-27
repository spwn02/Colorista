#pragma once

#include "Core.h"

class AppLayer : public Core::Layer
{
public:
  AppLayer();
  virtual ~AppLayer();

  void onAttach() override;
  void onDetach() override;
  void onEvent(Events::Event& event) override;

  void onUpdate(float ts) override;
  void onRender() override;
private:
  std::shared_ptr<Renderer::GraphicsShader> m_shader;
  std::shared_ptr<Renderer::VertexArray> m_vertexArray;
  std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
  std::shared_ptr<Renderer::Renderer> m_renderer;
};