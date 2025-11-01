#include "Corepch.h"

#include "OpenGLInput.h"
#include "Application.h"

namespace Core {

#define window (GLFWwindow*)Application::get().getWindow().getHandle()

  bool OpenGLInput::isKeyPressedImpl(uint32_t key)
  {
    return glfwGetKey(window, key);
  }

  bool OpenGLInput::isMouseButtonPressedImpl(uint32_t button)
  {
    return glfwGetMouseButton(window, button);
  }

  glm::vec2 OpenGLInput::getCursorPosImpl()
  {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { (float)x, (float)y };
  }

}