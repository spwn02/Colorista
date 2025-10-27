#pragma once

#include "Layer.h"
#include "Window.h"
#include "events/Event.h"
#include "renderer/RendererAPI.h"

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>

namespace Core {

  struct ApplicationSpecification
  {
    std::string name = "Application";
    Renderer::GraphicsAPI graphicsAPI = Renderer::OpenGL;
    WindowSpecification windowSpec;
  };

  class Application
  {
  public:
    Application(const ApplicationSpecification& specification = ApplicationSpecification());
    ~Application();

    void start();
    void shutdown();

    template<typename TLayer>
      requires(std::is_base_of_v<Layer, TLayer>)
    void pushLayer()
    {
      std::unique_ptr<TLayer> layer = std::make_unique<TLayer>();

      layer->onAttach();

      m_layerStack.push_back(std::move(layer));
    }

    template<typename TLayer>
      requires(std::is_base_of_v<Layer, TLayer>)
    void pushOverlay()
    {
      std::unique_ptr<TLayer> overlay = std::make_unique<TLayer>();

      overlay->onAttach();

      m_overlayStack.push_back(std::move(overlay));
    }

    glm::vec2 getFramebufferSize() const;
    static Application& get();
    inline Window& getWindow() const { return *m_window; }
    static float getTime();

    void onEvent(Events::Event& event);
  private:
    ApplicationSpecification m_specification;
    static Application* s_instance;
    std::shared_ptr<Window> m_window;
    bool m_running = false;

    std::vector<std::unique_ptr<Layer>> m_layerStack;
    std::vector<std::unique_ptr<Layer>> m_overlayStack;
  };

}