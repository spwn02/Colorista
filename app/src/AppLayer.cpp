#include "AppLayer.h"

#include "GLFW/glfw3.h"

AppLayer::AppLayer()
  : Layer("App")
{
  // Setup renderer
  m_renderer.reset(Renderer::Renderer::create());

  float vertices[] = {
     0.5f,  0.5f,
     0.5f, -0.5f,
    -0.5f, -0.5f,
    -0.5f,  0.5f,
  };

  m_vertexArray.reset(Renderer::VertexArray::create());
  m_vertexBuffer.reset(Renderer::VertexBuffer::create(nullptr, 0));

  m_indexBuffer.reset(Renderer::IndexBuffer::create(nullptr, 0));

  m_shader.reset(Renderer::GraphicsShader::create("shaders/v.shader", "shaders/f.shader"));

  Renderer::BufferLayout layout = {
    { Renderer::DataType::Float2, "i_position" },
  };

  m_vertexBuffer->setLayout(layout);
  m_vertexArray->addVertexBuffer(m_vertexBuffer, m_shader);
  m_vertexArray->setIndexBuffer(m_indexBuffer);

  m_vertices.reserve(1'000);
  m_indices.reserve(1'000);
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
  }
  else if (event.getType() == Events::MouseScrolled)
  {
    Events::MouseScrolledEvent& e = static_cast<Events::MouseScrolledEvent&>(event);
    m_sizePx = std::max(1.0f, m_sizePx + (e.y > 0 ? 1.0f : -1.0f));
  }
  else
  {
    Log::Trace("AppLayer: received event!");
  }

  event.handled = true;
}

void AppLayer::onUpdate(float ts)
{
  Core::Application& app = Core::Application::get();

  const glm::vec2 cursor = Core::Input::getCursorPos();
  const glm::vec2 fbs = app.getFramebufferSize(); // x - width, y - height
  const glm::vec2 cndc(
    cursor.x / fbs.x * 2.0f - 1.0f,
    1.0f - cursor.y / fbs.y * 2.0f
  ); // Current NDC

  // Brush size
  const glm::vec2 diameter(
    (m_sizePx / fbs.x) * 2.0f,
    (m_sizePx / fbs.y) * 2.0f
  );

  if (Core::Input::isMouseButtonPressed(0))
  {
    if (!m_hasLndc)
    {
      appendQuad(cndc, diameter);
      m_hasLndc = true;
    }
    else
    {
      const float spacing = std::min(diameter.x, diameter.y) / 2;
      const float dist = glm::length(cndc - m_lndc);
      const int steps = std::max(1, (int)std::ceil(dist / spacing));
      for (int i = 1; i <= steps; ++i)
      {
        glm::vec2 p(glm::mix(m_lndc, cndc, float(i) / steps));
        appendQuad(p, diameter);
      }
    }

    m_lndc = cndc;
  }
  else m_hasLndc = false;

  // Preview
  std::vector<Vertex> vertices;
  vertices.reserve(m_vertices.size() + 1);

  vertices.insert(vertices.end(), m_vertices.begin(), m_vertices.end());
  vertices.emplace_back(makeQuad(cndc, diameter));

  std::vector<Index> indices;
  indices.reserve(m_indices.size() + 1);

  indices.insert(indices.end(), m_indices.begin(), m_indices.end());

  const uint32_t baseIndex = getBaseIndex();
  const Index index = {
    baseIndex + 0, baseIndex + 1, baseIndex + 3,
    baseIndex + 1, baseIndex + 2, baseIndex + 3
  };
  indices.emplace_back(index);

  m_vertexBuffer->sendData(vertices.data()->data(), (uint32_t)vertices.size() * sizeof(Vertex));
  m_indexBuffer->set(indices.data()->data(), (uint32_t)indices.size() * sizeof(Index));
}

void AppLayer::onRender()
{
  m_renderer->clearColor(0.1f, 0.1f, 0.1f, 1.0f);
  m_renderer->clear();

  glm::vec2 framebufferSize = Core::Application::get().getFramebufferSize();
  
  m_renderer->setViewport(0, 0, framebufferSize.x, framebufferSize.y);

  m_renderer->bindFramebuffer(0);
  m_renderer->drawIndexed(m_vertexArray, m_shader);
}
