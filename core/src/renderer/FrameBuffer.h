#pragma once

#include <stdint.h>
#include <memory>

#include "Texture.h"

namespace Renderer {

  class FrameBuffer
  {
  public:
    virtual ~FrameBuffer() {};

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void resize(std::shared_ptr<Texture>& texture, int32_t width, int32_t height) = 0;
    inline void resize(std::shared_ptr<Texture>& texture, float width, float height) { resize(texture, (int32_t)width, (int32_t)height); };

    virtual void drawBuffer() const = 0;

    static FrameBuffer* create();
  protected:
    uint32_t m_rendererID = 0;
    uint32_t m_renderBuffer = 0;
  };

}