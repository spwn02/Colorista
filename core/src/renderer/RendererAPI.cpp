#include "Corepch.h"

#include "RendererAPI.h"

#include "platform/OpenGL/OpenGLSetup.h"

namespace Renderer {

  GraphicsAPI RendererAPI::s_API = Null;

  void RendererAPI::setAPI(GraphicsAPI API)
  {
    if (s_API == API) return Log::Trace("GraphicsAPI is already set to {0}", static_cast<int8_t>(API));

    GraphicsAPI oldAPI = s_API;

    switch (API)
    {
    case Null:
      Log::Assert(false, "Use RendererAPI::destroyAPI() instead of RendererAPI::setAPI(None)!");
      break;
    case OpenGL:
      OpenGLSetup::setup();
      break;
    default:
      Log::Assert(false, "GraphicsAPI({0}) is currently not supported!", static_cast<int8_t>(API));
      return;
    }

    if (oldAPI != Null) destroyAPI();
    s_API = API;
  }

  void RendererAPI::destroyAPI()
  {
    switch (s_API)
    {
    case Null:
      Log::Assert(false, "GraphicsAPI is not set yet!");
      break;
    case OpenGL:
      OpenGLSetup::shutdown();
      break;
    default:
      Log::Assert(false, "GraphicsAPI({0}) is currently not supported!", static_cast<int8_t>(s_API));
      break;
    }

    s_API = Null;
  }

}