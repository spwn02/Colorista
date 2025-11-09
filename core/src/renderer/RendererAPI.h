#pragma once

#include <stdint.h>

namespace Renderer {

  enum GraphicsAPI : int8_t
  {
    Null = 0, OpenGL, Vulkan
  };

  class RendererAPI
  {
  public:
    static void setAPI(GraphicsAPI API);
    static void destroyAPI();

    static GraphicsAPI getAPIType() { return s_API; }
    static int8_t getAPI() { return s_API; }
  private:
    static GraphicsAPI s_API;
  };

}