#include "Application.h"

#include <GLFW/glfw3.h>
#include "Log.h"

namespace Core {

  Application* Application::s_instance = nullptr;

  static void GLFWErrorCallback(int error, const char* description)
  {
    Log::Assert(false, "GLFW error({0}): {1}", error, description);
  }

  Application::Application(const ApplicationSpecification& specification)
    : m_specification(specification)
  {
    s_instance = this;

    Log::Log::init();

    glfwSetErrorCallback(GLFWErrorCallback);
    glfwInit();

    // Set window title to app name if empty
    if (m_specification.windowSpec.title.empty())
      m_specification.windowSpec.title = m_specification.name;

    m_window = std::make_shared<Window>(m_specification.windowSpec);
    m_window->start();
  }

  Application::~Application()
  {
    m_window->shutdown();

    glfwTerminate();

    s_instance = nullptr;
  }

  void Application::start()
  {
    m_running = true;

    float lastTime = getTime();

    // Main Application loop
    while (m_running)
    {
      glfwPollEvents();

      if (m_window->shouldClose())
      {
        shutdown();
        break;
      }

      float currentTime = getTime();
      float timestep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
      lastTime = currentTime;

      // Main layer update here
      for (const std::unique_ptr<Layer>& layer : m_layerStack)
        layer->onUpdate(timestep);

      // NOTE: rendering can be done elsewhere (eg. render thread)
      for (const std::unique_ptr<Layer>& layer : m_layerStack)
        layer->onRender();

      m_window->update();
    }
  }

  void Application::shutdown()
  {
    m_running = false;
  }

  glm::vec2 Application::getFramebufferSize() const
  {
    return m_window->getFramebufferSize();
  }

  Application& Application::get()
  {
    Log::Assert(s_instance, "The Application is not initialized yet!");
    return *s_instance;
  }

  float Application::getTime()
  {
    return (float)glfwGetTime();
  }

}