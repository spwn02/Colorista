#include "AppLayer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "imgui.h"

AppLayer::AppLayer(EditorState& state)
  : Layer("App"), m_state(state)
{
  // Setup renderer
  m_renderer.reset(Renderer::Renderer::create());
  m_state.texture.reset(Renderer::Texture::create(m_state.viewportSize.x, m_state.viewportSize.y));

  // Geometry
  m_vertexBuffer.reset(Renderer::VertexBuffer::create({}));
  m_indexBuffer.reset(Renderer::IndexBuffer::create({}));

  m_shader.reset(Renderer::GraphicsShader::create("shaders/v.shader", "shaders/f.shader"));

  Renderer::BufferLayout layout = {
    { Renderer::DataType::Float2, "i_position" },
    { Renderer::DataType::Float4, "i_color" },
  };

  m_vertexBuffer->setLayout(layout);
  m_renderer->getVertexArray()->addVertexBuffer(m_vertexBuffer, m_shader);
  m_renderer->getVertexArray()->setIndexBuffer(m_indexBuffer);
}

AppLayer::~AppLayer()
{

}

void AppLayer::onAttach()
{
  Log::Info("AppLayer: attached!");

}

void AppLayer::onDetach()
{

}

void AppLayer::onEvent(Events::Event& event)
{
  if (event.getType() == Events::KeyPressed)
  {
    Events::KeyPressedEvent& e = static_cast<Events::KeyPressedEvent&>(event);

    if (e.keyCode == GLFW_KEY_ESCAPE)
      Core::Application::get().shutdown();
      event.handled = true;
  }
  else if (event.getType() == Events::MouseScrolled)
  {
    Events::MouseScrolledEvent& e = static_cast<Events::MouseScrolledEvent&>(event);
    m_state.brushSize = std::max(1.0f, m_state.brushSize + (e.y > 0 ? 1.0f : -1.0f));
    event.handled = true;
  }
  else
  {
    //Log::Trace("AppLayer: received event!");
  }

}

void AppLayer::onUpdate(float ts)
{
  if (m_state.resetRequested || (Core::Input::isKeyPressed(GLFW_KEY_LEFT_CONTROL) && Core::Input::isKeyPressed(GLFW_KEY_R)))
  {
    m_meshBuffer.clear();
    m_state.resetRequested = false;
  }

  if (m_state.viewportHovered)
  {
    // Brush size in pixels -> diameter in NDC
    glm::vec2 ndc = {
      m_state.mouseUV.x * 2.0f - 1.0f,
      m_state.mouseUV.y * 2.0f - 1.0f
    };

    glm::vec2 diameter = {
      m_state.brushSize / std::max(1.0f, m_state.canvasSize.x) * 2.0f,
      m_state.brushSize / std::max(1.0f, m_state.canvasSize.y) * 2.0f
    };

    m_cPiece = generateShape(ndc, diameter);

    if (ImGui::IsMouseDown(0))
    {
      if (!m_hasLndc) {
        appendShape(m_cPiece);
        m_hasLndc = true;
      }
      else {
        // Clamp spacing to avoid huge step counts for tiny brushes
        const float spacing = std::min(diameter.x, diameter.y) / 2;
        const float dist = glm::length(ndc - m_lndc);
        const int steps = std::max(1, (int)std::ceil(dist / spacing));
        for (int i = 1; i <= steps; ++i)
        {
          glm::vec2 p(glm::mix(m_lndc, ndc, float(i) / steps));
          auto elem = generateShape(p, diameter);
          appendShape(elem);
        }
      }
      m_lndc = ndc;
    }
    else m_hasLndc = false;
  }
  else m_hasLndc = false;

  // Preview
  MeshBuffer mb = MeshBuffer();
  mb.vertices.reserve(m_meshBuffer.vertices.size() + m_cPiece.vertices.size());
  mb.indices.reserve(m_meshBuffer.indices.size() + m_cPiece.indices.size());

  mb.vertices.insert(mb.vertices.end(), m_meshBuffer.vertices.begin(), m_meshBuffer.vertices.end());
  mb.indices.insert(mb.indices.end(), m_meshBuffer.indices.begin(), m_meshBuffer.indices.end());

  const uint32_t base = (uint32_t)mb.vertices.size();
  mb.vertices.insert(mb.vertices.end(), m_cPiece.vertices.begin(), m_cPiece.vertices.end());
  for (uint32_t i : m_cPiece.indices)
    mb.indices.push_back(base + i);

  m_vertexBuffer->sendData((float*)mb.vertices.data(), (uint32_t)mb.vertices.size() * sizeof(Vertex));
  m_indexBuffer->set(mb.indices.data(), (uint32_t)mb.indices.size() * sizeof(uint32_t));
}

void AppLayer::onRender()
{
  m_renderer->getFrameBuffer()->bind();

  //Log::Info("{0}, {1}", m_state.viewportSize.x, m_state.viewportSize.y);
  const int fbw = (int)m_state.viewportSize.x;
  const int fbh = (int)m_state.viewportSize.y;

  static int lastW = -1, lastH = -1;
  if (fbw > 0 && fbh > 0 && (fbw != lastW || fbh != lastH)) {
    m_renderer->getFrameBuffer()->resize(m_state.texture, fbw, fbh);
    lastW = fbw; lastH = fbh;
  }

  m_renderer->setViewport(0, 0, fbw, fbh);

  m_renderer->clearColor(0.1f, 0.1f, 0.1f, 1.0f);
  m_renderer->clear();

  m_renderer->drawIndexed(m_shader);
}
