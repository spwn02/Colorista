#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Core {

  struct WindowSpecification
  {
    std::string title;
    uint32_t width = 1280;
    uint32_t height = 720;
    bool resizable = true;
    bool VSync = true;
  };

  class Window
  {
  public:
    virtual ~Window() = default;

    virtual void start() = 0;
    virtual void shutdown() = 0;

    virtual void update() = 0;
    virtual void pollEvents() = 0;

    virtual bool shouldClose() const = 0;

    virtual glm::vec2 getFramebufferSize() = 0;
    virtual void* getHandle() const = 0;
    virtual float getTime() const = 0;

    virtual void setVSync(bool VSync) const = 0;
    virtual void setResizable(bool resizable) const = 0;

    static Window* create(const WindowSpecification& specification = WindowSpecification());
  };

}