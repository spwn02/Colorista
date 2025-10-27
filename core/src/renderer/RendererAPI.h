#pragma once

#include <stdint.h>

namespace Renderer {

  enum GraphicsAPI : int8_t
  {
    None = 0, OpenGL, Vulcan
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