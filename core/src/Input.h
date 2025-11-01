#pragma once

#include "stdint.h"

#include "glm/glm.hpp"

namespace Core {

  class Input
  {
  public:
    static bool isKeyPressed(uint32_t key);
    static bool isMouseButtonPressed(uint32_t button);
    static glm::vec2 getCursorPos();
  };

}