#pragma once

#include "renderer/VertexArray.h"

namespace Renderer {

  class OpenGLVertexArray : public VertexArray
  {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray() override;

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(std::shared_ptr<VertexBuffer>& buffer, uint32_t program) override;
    virtual void setIndexBuffer(std::shared_ptr<IndexBuffer>& buffer) override;

    virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return m_vertexBuffers; }
    virtual inline const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return m_indexBuffer; }
  private:
    uint32_t m_rendererID;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
  };

}