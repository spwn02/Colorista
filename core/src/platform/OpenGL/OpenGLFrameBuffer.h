#pragma once

#include "renderer/FrameBuffer.h"

namespace Renderer {

  class OpenGLFrameBuffer : public FrameBuffer
  {
  public:
    OpenGLFrameBuffer();
    ~OpenGLFrameBuffer() override;

    void bind() const override;
    void unbind() const override;
    void resize(std::shared_ptr<Texture>& texture, int32_t width, int32_t height) override;

    void drawBuffer() const override;
  };

}