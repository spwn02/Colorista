#pragma once

#include "Layer.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>

namespace Core {

  struct ApplicationSpecification
  {
    std::string name = "Application";
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

    glm::vec2 getFramebufferSize() const;

    static Application& get();
    inline Window& getWindow() { return *m_window; }
    static float getTime();
  private:
    ApplicationSpecification m_specification;
    static Application* s_instance;
    std::shared_ptr<Window> m_window;
    bool m_running = false;

    std::vector<std::unique_ptr<Layer>> m_layerStack;
  };

}