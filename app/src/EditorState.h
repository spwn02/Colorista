#pragma once

#include <glm/glm.hpp>
#include <stdint.h>

#include "Core.h"

enum class BrushType : uint8_t {
  Square = 0, Triangle, TriangleC, Circle
};

struct EditorState {

  // Drawing
  bool resetRequested = true;
  float brushSize = 10.0f;
  glm::vec4 brushColor{ 1.0f, 1.0f, 1.0f, 1.0f };
  BrushType brushType = BrushType::Square;

  // Canvas
  glm::vec2 canvasSize{ 1920, 1080 };
  glm::vec2 pan{ 0, 0 };
  bool centerView = true;
  bool viewportHovered = false;
  glm::vec2 mouseUV{ 0.0f, 0.0f };

  // UI
  bool darkMode = true;
  bool showStats = false;

  // Render
  std::shared_ptr<Renderer::Texture> texture = nullptr;
  glm::vec2 viewportSize{ 0.0f, 0.0f };

};