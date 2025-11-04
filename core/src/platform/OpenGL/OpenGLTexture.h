#pragma once

#include "renderer/Texture.h"

namespace Renderer {

  class OpenGLTexture : public Texture
  {
  public:
    OpenGLTexture(int32_t width, int32_t height);
    ~OpenGLTexture() override;

    void bind() const override;
    void unbind() const override;

    void resize(int32_t width, int32_t height) override;
    void uploadRgba(glm::vec2 size, std::vector<uint8_t>& rgba) override;
  };

}