#include "Corepch.h"

#include "OpenGLWindow.h"
#include "OpenGLSetup.h"

#include "events/ApplicationEvents.h"
#include "events/KeyEvents.h"
#include "events/MouseEvents.h"

#include "Application.h"

namespace Core {

  OpenGLWindow::OpenGLWindow(const WindowSpecification& specification)
    : m_specification(specification)
  {

  }

  OpenGLWindow::~OpenGLWindow()
  {
    shutdown();
  }

  void OpenGLWindow::start()
  {
    using namespace Events;

    setResizable(m_specification.resizable);

    m_handle = glfwCreateWindow(m_specification.width, m_specification.height, m_specification.title.c_str(), nullptr, nullptr);

    Log::Assert(m_handle, "Failed to create GLFW window!");

    glfwMakeContextCurrent(m_handle);
    Renderer::OpenGLSetup::loadGlad();

    setVSync(m_specification.VSync);

    glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      switch (action)
      {
      case GLFW_PRESS:
      {
        KeyPressedEvent event(key, scancode, mods, 0);
        Application::get().onEvent(event);
        break;
      }
      case GLFW_RELEASE:
      {
        KeyReleasedEvent event(key, scancode, mods);
        Application::get().onEvent(event);
        break;
      }
      case GLFW_REPEAT:
      {
        KeyPressedEvent event(key, scancode, mods, 1);
        Application::get().onEvent(event);
        break;
      }
      }
      });

    glfwSetCharCallback(m_handle, [](GLFWwindow* window, unsigned int keycode) {
      KeyTypedEvent event(keycode);
      Application::get().onEvent(event);
      });

    glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double xpos, double ypos) {
      MouseMovedEvent event(xpos, ypos);
      Application::get().onEvent(event);
      });

    glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods) {
      switch (action)
      {
      case GLFW_PRESS:
      {
        MouseButtonPressedEvent event(button, mods);
        Application::get().onEvent(event);
        break;
      }
      case GLFW_RELEASE:
      {
        MouseButtonReleasedEvent event(button);
        Application::get().onEvent(event);
        break;
      }
      }
      });

    glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xoffset, double yoffset) {
      MouseScrolledEvent event(xoffset, yoffset);
      Application::get().onEvent(event);
      });

    glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window) {
      WindowCloseEvent event(window);
      Application::get().onEvent(event);
      });

    glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height) {
      WindowResizeEvent event(window, width, height);
      Application::get().onEvent(event);
      });

    glfwSetWindowFocusCallback(m_handle, [](GLFWwindow* window, int focused) {
      if (focused == GL_TRUE)
      {
        WindowFocusEvent event(window);
        Application::get().onEvent(event);
      }
      else
      {
        WindowLostFocusEvent event(window);
        Application::get().onEvent(event);
      }
      });

    glfwSetWindowPosCallback(m_handle, [](GLFWwindow* window, int xpos, int ypos) {
      WindowMovedEvent event(window, xpos, ypos);
      Application::get().onEvent(event);
      });
  }

  void OpenGLWindow::shutdown()
  {
    if (m_handle)
      glfwDestroyWindow(m_handle);

    m_handle = nullptr;
  }

  void OpenGLWindow::update()
  {
    glfwSwapBuffers(m_handle);
  }

  glm::vec2 OpenGLWindow::getFramebufferSize()
  {
    int width, height;
    glfwGetFramebufferSize(m_handle, &width, &height);
    return { width, height };
  }

  bool OpenGLWindow::shouldClose() const
  {
    return glfwWindowShouldClose(m_handle) != 0;
  }

}