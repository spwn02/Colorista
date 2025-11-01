#pragma once

#include "Input.h"
#include "GLFW/glfw3.h"

namespace Core {

  class OpenGLInput : public Input
  {
  public:
    static bool isKeyPressedImpl(uint32_t key);
    static bool isMouseButtonPressedImpl(uint32_t button);
    static glm::vec2 getCursorPosImpl();
  };

}