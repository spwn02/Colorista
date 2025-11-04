#pragma once

#include "renderer/Renderer.h"

namespace Renderer {

  class OpenGLRenderer : public Renderer
  {
  public:
    void clear() const override;
    void clearColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a) const override;
    void clearColor(float r, float g, float b, float a) const override;
    void setViewport(int32_t x, int32_t y, float width, float height) const override;

    void drawIndexed(const std::shared_ptr<Shader>& shader) const override;
    void drawCount(
      const std::shared_ptr<Shader>& shader,
      uint32_t first,
      uint32_t count) const override;
  };

}