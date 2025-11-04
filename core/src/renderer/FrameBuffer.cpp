#include "FrameBuffer.h"

#include "RendererAPI.h"
#include "platform/OpenGL/OpenGLFrameBuffer.h"

namespace Renderer {

  FrameBuffer* FrameBuffer::create()
  {
    FrameBuffer* buffer = nullptr;

    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      buffer = new OpenGLFrameBuffer();
      break;
    default:
      return nullptr;
    }

    buffer->drawBuffer();
    return buffer;
  }

}