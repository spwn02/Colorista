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

  void OpenGLRenderer::setViewport(int32_t x, int32_t y, int32_t width, int32_t height) const
  {
    glViewport(0, 0, static_cast<size_t>(width), static_cast<size_t>(height));
  }

  void OpenGLRenderer::drawIndexed(
    const std::shared_ptr<VertexArray>& vertexArray,
    const std::shared_ptr<Shader>& shader) const
  {
    shader->bind();
    vertexArray->bind();
    shader->unbind();

    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    vertexArray->unbind();
  }

  void OpenGLRenderer::drawCount(
    const std::shared_ptr<VertexArray>& vertexArray,
    const std::shared_ptr<Shader>& shader,
    uint32_t first,
    uint32_t count) const
  {
    shader->bind();
    vertexArray->bind();

    glDrawArrays(GL_TRIANGLES, first, count);

    shader->unbind();
    vertexArray->unbind();
  }

  void OpenGLRenderer::bindFramebuffer(uint32_t frameBuffer) const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  }

}