#include "Corepch.h"

#include "Application.h"

namespace Core {

  Application* Application::s_instance = nullptr;

  Application::Application(const ApplicationSpecification& specification)
    : m_specification(specification)
  {
    s_instance = this;

    Log::Log::init();
    Renderer::RendererAPI::setAPI(m_specification.graphicsAPI);

    // Set window title to app name if empty
    if (m_specification.windowSpec.title.empty())
      m_specification.windowSpec.title = m_specification.name;

    m_window.reset(Window::create(m_specification.windowSpec));
    m_window->start();
  }

  Application::~Application()
  {
    for (const std::unique_ptr<Layer>& layer : m_layerStack)
      layer->onDetach();
    m_layerStack.clear();

    m_window->shutdown();

    Renderer::RendererAPI::destroyAPI();

    s_instance = nullptr;
  }

  void Application::start()
  {
    m_running = true;

    float lastTime = getTime();

    // Main Application loop
    while (m_running)
    {
      m_window->pollEvents();

      if (m_window->shouldClose())
      {
        shutdown();
        break;
      }

      float currentTime = getTime();
      float timestep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
      lastTime = currentTime;

      // Updates
      for (const std::unique_ptr<Layer>& layer : m_layerStack)
        layer->onUpdate(timestep);

      // Renders
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
    return Application::get().getWindow().getTime();
  }

  void Application::onEvent(Events::Event& event)
  {
    for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
    {
      (*it)->onEvent(event);
      if (event.handled) break;
    }
  }

}