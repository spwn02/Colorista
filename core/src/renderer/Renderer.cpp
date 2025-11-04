#include "Corepch.h"

#include "Renderer.h"
#include "RendererAPI.h"

#include "platform/OpenGL/OpenGLRenderer.h"

namespace Renderer {

  Renderer::Renderer()
  {
    m_vertexArray.reset(VertexArray::create());
    m_frameBuffer.reset(FrameBuffer::create());
  }

  Renderer* Renderer::create()
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      return new OpenGLRenderer();
    default:
      return nullptr;
    }
  }

}