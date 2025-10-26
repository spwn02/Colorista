#include "Window.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Log.h"

namespace Core {

  Window::Window(const WindowSpecification& specification)
    : m_specification(specification)
  {

  }

  Window::~Window()
  {
    shutdown();
  }

  void Window::start()
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(m_specification.width, m_specification.height, m_specification.title.c_str(), nullptr, nullptr);

    Log::Assert(m_handle, "Failed to create GLFW window!");

    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_handle));
    gladLoadGL();
  }

  void Window::shutdown()
  {
    if (m_handle)
      glfwDestroyWindow(static_cast<GLFWwindow*>(m_handle));

    m_handle = nullptr;
  }

  void Window::update()
  {
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_handle));
  }

  glm::vec2 Window::getFramebufferSize()
  {
    int width, height;
    glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_handle), &width, &height);
    return { width, height };
  }

  bool Window::shouldClose() const
  {
    return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_handle)) != 0;
  }

}