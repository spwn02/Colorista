#pragma once

#include <stdint.h>
#include <vector>
#include <glm/glm.hpp>

namespace Renderer {

  class Texture
  {
  public:
    virtual ~Texture() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void resize(int32_t width, int32_t height) = 0;
    virtual void uploadRgba(glm::vec2 size, std::vector<uint8_t>& rgba) = 0;

    virtual inline void putPx(std::vector<uint8_t>& px, glm::vec3 coords, glm::vec4 color)
    {
      size_t i = ((size_t)coords.y * (size_t)coords.z + (size_t)coords.x) * 4;
      px[i + 0] = (uint8_t)color.r;
      px[i + 1] = (uint8_t)color.g;
      px[i + 2] = (uint8_t)color.b;
      px[i + 3] = (uint8_t)color.a;
    }

    uint32_t getTextureID() { return m_textureID; }

    static Texture* create(int32_t width, int32_t height);
    static Texture* create(glm::vec2 size) { return create((int32_t)size.x, (int32_t)size.y); };
  protected:
    uint32_t m_textureID;
  };

}