#pragma once

namespace Renderer {

  class OpenGLSetup
  {
  public:
    static void setup();
    static void loadGlad();
    static void shutdown();
  private:
    static bool s_initialized;
    static bool s_gladLoaded;
  };

}