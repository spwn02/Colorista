#include "OpenGLFrameBuffer.h"
#include "Log.h"

#include <glad/glad.h>

namespace Renderer {

  OpenGLFrameBuffer::OpenGLFrameBuffer()
  {
    glCreateFramebuffers(1, &m_rendererID);
    glCreateRenderbuffers(1, &m_renderBuffer);
  }

  OpenGLFrameBuffer::~OpenGLFrameBuffer()
  {
    glDeleteFramebuffers(1, &m_rendererID);
    glDeleteRenderbuffers(1, &m_renderBuffer);
  }

  void OpenGLFrameBuffer::resize(std::shared_ptr<Texture>& texture, int32_t width, int32_t height)
  {
    bind();

    // Reallocate color
    texture->resize(width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getTextureID(), 0);

    // Reallocate depth-stencil
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      Log::Assert(false, "Framebuffer is not complete!");
  }

  void OpenGLFrameBuffer::bind() const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
  }

  void OpenGLFrameBuffer::unbind() const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void OpenGLFrameBuffer::drawBuffer() const
  {
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
  }

}