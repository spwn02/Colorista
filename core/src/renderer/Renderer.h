#pragma once

#include "Shader.h"
#include "VertexArray.h"

namespace Renderer {

  class Renderer
  {
  public:
    virtual void clear() const = 0;
    virtual void clearColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a) const = 0;
    virtual void clearColor(float r, float g, float b, float a) const = 0;
    virtual void setViewport(int32_t x, int32_t y, float width, float height) const = 0;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) const = 0;
    virtual void drawCount(
      const std::shared_ptr<VertexArray>& vertexArray,
      const std::shared_ptr<Shader>& shader,
      uint32_t first,
      uint32_t count) const = 0;
    virtual void bindFramebuffer(uint32_t frameBuffer) const = 0;

    static Renderer* create();
  };

}