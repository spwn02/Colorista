#pragma once

#include <vector>
#include "Buffer.h"

namespace Renderer {

  class VertexArray
  {
  public:
    virtual ~VertexArray() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(std::shared_ptr<VertexBuffer>& buffer, uint32_t program) = 0;
    virtual void setIndexBuffer(std::shared_ptr<IndexBuffer>& buffer) = 0;

    virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
    virtual inline const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

    static VertexArray* create();
  };

}