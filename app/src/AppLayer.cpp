#include "AppLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

AppLayer::AppLayer()
  : Layer("App")
{
  // Setup renderer
  m_renderer.reset(Renderer::Renderer::create());

  // Create shaders
  m_shader.reset(Renderer::GraphicsShader::create("shaders/vertex.shader", "shaders/fractals.shader"));

  // Create geometry
  Renderer::BufferLayout layout = {
    { Renderer::DataType::Float2, "a_Position" }
  };

  float vertices[] = {
    -1.0f, -1.0f,  // Bottom-left
     3.0f, -1.0f,  // Bottom-right
    -1.0f,  3.0f   // Top-left
  };

  m_vertexArray.reset(Renderer::VertexArray::create());
  m_vertexBuffer.reset(Renderer::VertexBuffer::create(vertices, sizeof(vertices)));

  m_vertexBuffer->setLayout(layout);

  m_vertexArray->addVertexBuffer(m_vertexBuffer, m_shader);
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
  Log::Trace("AppLayer: received event!");
  event.handled = true;
}

void AppLayer::onUpdate(float ts)
{

}

void AppLayer::onRender()
{
  m_renderer->clearColor(0.1f, 0.1f, 0.1f, 1);
  m_renderer->clear();

  m_shader->bind();

  // Uniforms
  m_shader->setUniform1f("iTime", Core::Application::getTime());

  glm::vec2 framebufferSize = Core::Application::get().getFramebufferSize();
  m_shader->setUniform2f("iResolution", framebufferSize.x, framebufferSize.y);

  m_renderer->setViewport(0, 0, framebufferSize.x, framebufferSize.y);

  // Render
  m_renderer->bindFramebuffer(0);
  m_renderer->drawCount(m_vertexArray, m_shader, 0, 3);
}