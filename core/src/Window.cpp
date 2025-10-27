#include "Corepch.h"

#include "Window.h"
#include "renderer/RendererAPI.h"

#include "platform/OpenGL/OpenGLWindow.h"

namespace Core {

  Window* Window::create(const WindowSpecification& specification)
  {
    using Renderer::RendererAPI;

    switch (RendererAPI::getAPI())
    {
    case Renderer::OpenGL:
      return new OpenGLWindow(specification);
    default:
      Log::Assert(false, "GraphicsAPI({0}) is currently not supported!", RendererAPI::getAPI());
      return nullptr;
    }
  }

}