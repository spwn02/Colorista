#include "Corepch.h"

#include "OpenGLBuffer.h"

namespace Renderer {

  OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
  {
    glCreateBuffers(1, &m_rendererID);
    bind();
    sendData(vertices, size);
  }

  void OpenGLVertexBuffer::sendData(float* vertices, uint32_t size) const
  {
    glNamedBufferData(m_rendererID, size, vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &m_rendererID);
  }

  void OpenGLVertexBuffer::bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
  }

  void OpenGLVertexBuffer::unbind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size)
    : m_count(size / sizeof(uint32_t))
  {
    glGenBuffers(1, &m_rendererID);
    bind();
    set(indices, size);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &m_rendererID);
  }

  void OpenGLIndexBuffer::bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
  }

  void OpenGLIndexBuffer::unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void OpenGLIndexBuffer::set(uint32_t* indices, uint32_t size) const
  {
    m_count = size / sizeof(uint32_t);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glNamedBufferData(m_rendererID, size, indices, GL_STATIC_DRAW);
  }

}