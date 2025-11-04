#include "Corepch.h"

#include "OpenGLRenderer.h"

namespace Renderer {

  void OpenGLRenderer::clear() const
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRenderer::clearColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a) const
  {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
  }

  void OpenGLRenderer::clearColor(float r, float g, float b, float a) const
  {
    glClearColor(r, g, b, a);
  }

  void OpenGLRenderer::setViewport(int32_t x, int32_t y, float width, float height) const
  {
    glViewport(0, 0, (int32_t)width, (int32_t)height);
  }

  void OpenGLRenderer::drawIndexed(
    const std::shared_ptr<Shader>& shader) const
  {
    Log::Assert(m_vertexArray->getIndexBuffer() != nullptr, "IndexBuffer has not been initialized!");

    m_frameBuffer->bind();
    shader->bind();
    m_vertexArray->bind();

    glDrawElements(GL_TRIANGLES, m_vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    m_frameBuffer->unbind();
    shader->unbind();
    m_vertexArray->unbind();
  }

  void OpenGLRenderer::drawCount(
    const std::shared_ptr<Shader>& shader,
    uint32_t first,
    uint32_t count) const
  {
    m_frameBuffer->bind();
    shader->bind();
    m_vertexArray->bind();

    glDrawArrays(GL_TRIANGLES, first, count);

    shader->unbind();
    m_vertexArray->unbind();
    m_frameBuffer->unbind();
  }

}