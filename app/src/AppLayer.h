#pragma once

#include "Core.h"

class AppLayer : public Core::Layer
{
public:
  AppLayer();
  ~AppLayer();

  void onAttach() override;
  void onDetach() override;
  void onEvent(Events::Event& event) override;

  void onUpdate(float ts) override;
  void onRender() override;
private:
  using Vertex = std::array<float, 8>;
  using Index = std::array<uint32_t, 6>;

  inline Vertex makeQuad(glm::vec2 c, glm::vec2 d) const
  {
    return {
      c.x + d.x, c.y - d.y,
      c.x + d.x, c.y + d.y,
      c.x - d.x, c.y + d.y,
      c.x - d.x, c.y - d.y,
    };
  }
  void appendQuad(glm::vec2 c, glm::vec2 d)
  {
    const uint32_t base = getBaseIndex();
    m_vertices.emplace_back(makeQuad(c, d));
    m_indices.push_back({
      base + 0, base + 1, base + 3,
      base + 1, base + 2, base + 3
    });
  }

  inline const uint32_t getBaseIndex() const
  {
    return (uint32_t)m_vertices.size() * 4;
  }
private:
  std::shared_ptr<Renderer::GraphicsShader> m_shader;
  std::shared_ptr<Renderer::VertexArray> m_vertexArray;
  std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
  std::shared_ptr<Renderer::IndexBuffer> m_indexBuffer;
  std::shared_ptr<Renderer::Renderer> m_renderer;

  std::vector<Vertex> m_vertices;
  std::vector<Index> m_indices;
  bool m_hasLndc = false;
  glm::vec2 m_lndc{}; // Last NDC
  float m_sizePx = 10.0f;
};