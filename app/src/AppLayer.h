#pragma once

#include "Core.h"
#include "EditorState.h"

static constexpr float PI = 3.1415926535f;
static constexpr float PI2 = PI*2;

class AppLayer : public Core::Layer
{
public:
  AppLayer(EditorState& state);
  ~AppLayer();

  void onAttach() override;
  void onDetach() override;
  void onEvent(Events::Event& event) override;

  void onUpdate(float ts) override;
  void onRender() override;
private:

  struct Vertex
  {
    glm::vec2 pos;
    glm::vec4 color;

    Vertex(glm::vec2 pos, glm::vec4 color)
      : pos(pos), color(color) { }
  };

  struct MeshBuffer
  {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    MeshBuffer() {
      vertices.reserve(1'000);
      indices.reserve(1'000);
    }
    void clear() { vertices.clear(); indices.clear(); }
  };

  struct MeshPiece
  {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
  };

  inline MeshPiece makeQuad(glm::vec2 c, glm::vec2 d, glm::vec4 color) const
  {
    glm::vec2 r(d.x / 2, d.y / 2);

    return {
      { // Vertices
        { { c.x + r.x, c.y - r.y }, color },
        { { c.x + r.x, c.y + r.y }, color },
        { { c.x - r.x, c.y + r.y }, color },
        { { c.x - r.x, c.y - r.y }, color },
      },
      { // Indices
        0, 1, 3,
        1, 2, 3
      }
    };
  }

  inline MeshPiece makeTrig(glm::vec2 c, glm::vec2 d, glm::vec4 color, bool centered = false) const
  {
    glm::vec2 r(d.x / 2, d.y / 2);

    return {
      { // Vertices
        {{ c.x - r.x, c.y - r.y }, color},
        {{ c.x + r.x, c.y - r.y }, color},
        {{ centered ? c.x : (c.x - r.x), c.y + r.y }, color }
      },
      { // Indices
        0, 1, 2
      }
    };
  }

  inline MeshPiece makeNgon(glm::vec2 c, glm::vec2 d, glm::vec4 color, int32_t segments = 32) const
  {
    glm::vec2 r(d.x / 2, d.y / 2);

    MeshPiece buffer;
    buffer.vertices.reserve(1 + segments);
    buffer.indices.reserve(segments * 3);

    // Center
    buffer.vertices.push_back({ c, color });

    for (int i = 0; i < segments; ++i)
    {
      float a = i * (PI2 / segments);
      buffer.vertices.push_back({ { c.x + std::cos(a) * r.x, c.y + std::sin(a) * r.y }, color });
      buffer.indices.push_back(0);
      buffer.indices.push_back(1 + i);
      buffer.indices.push_back(1 + ((i+1) % segments));
    }

    return buffer;
  }

  inline void appendShape(MeshPiece& shape)
  {
    const uint32_t base = getBaseIndex();
    m_meshBuffer.vertices.insert(m_meshBuffer.vertices.end(), shape.vertices.begin(), shape.vertices.end());
    m_meshBuffer.indices.reserve(m_meshBuffer.indices.size() + shape.indices.size());
    for (uint32_t i : shape.indices) m_meshBuffer.indices.push_back(base + i);
  }

  const inline MeshPiece generateShape(glm::vec2 ndc, glm::vec2 diameter) const
  {
    switch (m_state.brushType)
    {
    case BrushType::Square:
    {
      return makeQuad(ndc, diameter, m_state.brushColor);
    }
    case BrushType::Triangle:
    {
      return makeTrig(ndc, diameter, m_state.brushColor);
    }
    case BrushType::TriangleC:
    {
      return makeTrig(ndc, diameter, m_state.brushColor, true);
    }
    case BrushType::Circle:
    {
      return makeNgon(ndc, diameter, m_state.brushColor);
    }
    default:
      Log::Assert(false, "Unknown BrushType!");
      return MeshPiece();
    }
  }

  inline const uint32_t getBaseIndex() const
  {
    return (uint32_t)m_meshBuffer.vertices.size();
  }
private:
  std::shared_ptr<Renderer::GraphicsShader> m_shader;
  std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
  std::shared_ptr<Renderer::IndexBuffer> m_indexBuffer;
  std::shared_ptr<Renderer::Renderer> m_renderer;

  MeshBuffer m_meshBuffer = MeshBuffer();
  bool m_hasLndc = false;
  glm::vec2 m_lndc{}; // Last NDC
  
  EditorState& m_state;
  MeshPiece m_cPiece;
};