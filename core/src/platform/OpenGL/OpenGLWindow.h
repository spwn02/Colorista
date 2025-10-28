#pragma once

#include "Window.h"

struct GLFWwindow {};

namespace Core {

  class OpenGLWindow : public Window
  {
  public:
    OpenGLWindow(const WindowSpecification& specification = WindowSpecification());
    ~OpenGLWindow() override;

    void start() override;
    void shutdown() override;

    void update() override;
    void pollEvents() override { glfwPollEvents(); }

    bool shouldClose() const override;

    glm::vec2 getFramebufferSize() override;
    void* getHandle() const override { return m_handle; };
    float getTime() const override { return static_cast<float>(glfwGetTime()); }

    void setVSync(bool VSync) const override { glfwSwapInterval(VSync); };
    void setResizable(bool resizable) const override { glfwWindowHint(GLFW_RESIZABLE, resizable); };
  private:
    WindowSpecification m_specification;

    GLFWwindow* m_handle = nullptr;
  };

}