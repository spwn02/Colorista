#include "Corepch.h"

#include "VertexArray.h"
#include "renderer/RendererAPI.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Renderer {

  VertexArray* VertexArray::create()
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      return new OpenGLVertexArray();
    default:
      return nullptr;
    }
  }

}