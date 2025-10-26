#pragma once

#include <glad/glad.h>

#include <filesystem>

namespace Renderer {

  struct Texture
  {
    GLuint handle = 0;
    uint32_t width = 0;
    uint32_t height = 0;
  };

  struct Framebuffer
  {
    GLuint handle = 0;
    Texture colorAttachment;
  };

  Texture createTexture(int width, int height);
  Texture loadTexture(const std::filesystem::path& path);
  Framebuffer createFramebufferWithTexture(const Texture texture);
  bool attachTextureToFramebuffer(Framebuffer& framebuffer, const Texture texture);
  void blitFramebufferToSwapchain(const Framebuffer framebuffer);
}