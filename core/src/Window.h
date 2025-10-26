#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Core {

  struct WindowSpecification
  {
    std::string title;
    uint32_t width = 1280;
    uint32_t height = 720;
    bool resizeable = true;
    bool VSync = true;
  };

  class Window
  {
  public:
    Window(const WindowSpecification& specification = WindowSpecification());
    ~Window();

    void start();
    void shutdown();

    void update();

    glm::vec2 getFramebufferSize();

    bool shouldClose() const;

    void* getHandle() const { return m_handle; }
  private:
    WindowSpecification m_specification;

    void* m_handle = nullptr;
  };

}