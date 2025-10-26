#include "AppLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

AppLayer::AppLayer()
  : Layer("App")
{
  // Create shaders
  m_shader = Renderer::createGraphicsShader("../../../../app/shaders/vertex.shader", "../../../../app/shaders/fragment.shader");

  // Create geometry
  glCreateVertexArrays(1, &m_vertexArray);
  glCreateBuffers(1, &m_vertexBuffer);

  struct Vertex
  {
    glm::vec2 position;
  };

  Vertex vertices[] = {
    { {-1.0f, -1.0f } },  // Bottom-left
    { { 3.0f, -1.0f } },  // Bottom-right
    { {-1.0f,  3.0f } }   // Top-left
  };

  glNamedBufferData(m_vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Bind the VBO to VAO at binding index 0
  glVertexArrayVertexBuffer(m_vertexArray, 0, m_vertexBuffer, 0, sizeof(Vertex));

  // Enable attributes
  glEnableVertexArrayAttrib(m_vertexArray, 0); // position
  
  // Format: location, size, type, normalized, relative offset
  glVertexArrayAttribFormat(m_vertexArray, 0, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, position)));

  // Link attribute locations to binding index 0
  glVertexArrayAttribBinding(m_vertexArray, 0, 0);
}

AppLayer::~AppLayer()
{
  glDeleteVertexArrays(1, &m_vertexArray);
  glDeleteBuffers(1, &m_vertexBuffer);

  glDeleteProgram(m_shader);
}


void AppLayer::onAttach()
{
  Log::Info("AppLayer: attached!");
}

void AppLayer::onDetach()
{

}

void AppLayer::onEvent(Core::Event& event)
{
  Log::Info("AppLayer: received event!");
}

void AppLayer::onUpdate(float ts)
{

}

void AppLayer::onRender()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(m_shader);

  // Uniforms
  glUniform1f(0, Core::Application::getTime());

  glm::vec2 framebufferSize = Core::Application::get().getFramebufferSize();
  glUniform2f(1, framebufferSize.x, framebufferSize.y);

  glViewport(0, 0, static_cast<GLsizei>(framebufferSize.x), static_cast<GLsizei>(framebufferSize.y));

  // Render
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindVertexArray(m_vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}