#include "Corepch.h"

#include "OpenGLWindow.h"
#include "OpenGLSetup.h"

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
    m_handle = glfwCreateWindow(m_specification.width, m_specification.height, m_specification.title.c_str(), nullptr, nullptr);

    Log::Assert(m_handle, "Failed to create GLFW window!");

    glfwMakeContextCurrent(m_handle);
    Renderer::OpenGLSetup::loadGlad();
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