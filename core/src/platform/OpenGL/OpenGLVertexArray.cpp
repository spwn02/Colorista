#include "Corepch.h"

#include "OpenGLVertexArray.h"

namespace Renderer {

  OpenGLVertexArray::OpenGLVertexArray()
  {
    glCreateVertexArrays(1, &m_rendererID);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    glDeleteVertexArrays(1, &m_rendererID);
  }

  void OpenGLVertexArray::bind() const
  {
    glBindVertexArray(m_rendererID);
  }

  void OpenGLVertexArray::unbind() const
  {
    glBindVertexArray(0);
  }

  static GLenum DataTypeToOpenGLType(DataType type)
  {
    switch (type)
    {
    case DataType::Float:   return GL_FLOAT;
    case DataType::Float2:  return GL_FLOAT;
    case DataType::Float3:  return GL_FLOAT;
    case DataType::Float4:  return GL_FLOAT;
    case DataType::Mat3:    return GL_FLOAT;
    case DataType::Mat4:    return GL_FLOAT;
    case DataType::Int:     return GL_INT;
    case DataType::Int2:    return GL_INT;
    case DataType::Int3:    return GL_INT;
    case DataType::Int4:    return GL_INT;
    case DataType::Boolean:    return GL_BOOL;
    }

    Log::Assert(false, "Unknown DataType!");
    return 0;
  }

  void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer, const std::shared_ptr<Shader>& shader)
  {
    Log::Assert(buffer->getLayout().getElements().size(), "Vertex buffer has no layout!");

    bind();
    buffer->bind();

    int32_t location;
    const BufferLayout& layout = buffer->getLayout();

    for (const auto& elem : layout)
    {
      location = glGetAttribLocation(shader->getHandle(), elem.name.c_str());

      glEnableVertexAttribArray(location);
      glVertexAttribPointer(
        location,
        elem.getComponentCount(),
        DataTypeToOpenGLType(elem.type),
        elem.normalized ? GL_TRUE : GL_FALSE,
        layout.getStride(),
        (const void*)elem.offset
      );
    }

    m_vertexBuffers.push_back(buffer);
  }

  void OpenGLVertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer>& buffer)
  {
    bind();
    buffer->bind();
    m_indexBuffer = buffer;
  }

}