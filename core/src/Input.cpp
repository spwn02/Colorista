#include "Corepch.h"

#include "Input.h"

#include "platform/OpenGL/OpenGLInput.h"

namespace Core {

  bool Input::isKeyPressed(uint32_t key)
  {
    return OpenGLInput::isKeyPressedImpl(key);
  }

  bool Input::isMouseButtonPressed(uint32_t button)
  {
    return OpenGLInput::isMouseButtonPressedImpl(button);
  }

  glm::vec2 Input::getCursorPos()
  {
    return OpenGLInput::getCursorPosImpl();
  }

}