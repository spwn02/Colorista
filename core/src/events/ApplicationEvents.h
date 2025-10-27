#pragma once

#include "Event.h"

#include <sstream>

namespace Events {

  struct WindowCloseEvent : Event
  {
    void* window;

    WindowCloseEvent(void* window)
      : window(window) { }

    EVENT_CLASS_TYPE(WindowClose)
  };

  struct WindowResizeEvent : Event
  {
    void* window;
    int32_t width, height;

    WindowResizeEvent(void* window, int32_t width, int32_t height)
      : window(window), width(width), height(height) { }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "WindowResizeEvent: " << width << ", " << height;
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
  };

  struct WindowFocusEvent : Event
  {
    void* window;

    WindowFocusEvent(void* window)
      : window(window) { }

    EVENT_CLASS_TYPE(WindowFocus)
  };

  struct WindowLostFocusEvent : Event
  {
    void* window;

    WindowLostFocusEvent(void* window)
      : window(window) { }

    EVENT_CLASS_TYPE(WindowLostFocus)
  };

  struct WindowMovedEvent : Event
  {
    void* window;
    int32_t xpos, ypos;

    WindowMovedEvent(void* window, int32_t xpos, int32_t ypos)
      : window(window), xpos(xpos), ypos(ypos) { }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "WindowMovedEvent: " << xpos << ", " << ypos;
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowLostFocus)
  };

  struct AppTickEvent : Event
  {
    AppTickEvent() {}

    EVENT_CLASS_TYPE(AppTick)
  };

  struct AppUpdateEvent : Event
  {
    AppUpdateEvent() {}

    EVENT_CLASS_TYPE(AppUpdate)
  };

  struct AppRenderEvent : Event
  {
    AppRenderEvent() {}

    EVENT_CLASS_TYPE(AppRender)
  };

}