#pragma once

#include "renderer/Buffer.h"

namespace Renderer {

  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer() override;

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void sendData(float* vertices, uint32_t size) const override;

    virtual inline const BufferLayout& getLayout() const override { return m_layout; }
    virtual inline void setLayout(BufferLayout layout) override { m_layout = layout; }
  private:
    uint32_t m_rendererID;
    BufferLayout m_layout;
  };

  class OpenGLIndexBuffer : public IndexBuffer
  {
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
    virtual ~OpenGLIndexBuffer() override;

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set(uint32_t* indices, uint32_t size) const override;

    virtual inline uint32_t getCount() const override { return m_count; }
  private:
    uint32_t m_rendererID;
    mutable uint32_t m_count;
  };

}