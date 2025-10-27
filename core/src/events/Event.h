#pragma once

#include <string>

namespace Events {

  enum EventType : int8_t
  {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
  };

  struct Event
  {
    bool handled = false;

    Event() = default;
    virtual ~Event() = default;

    virtual EventType getType() const = 0;
    virtual const char* getName() const = 0;
    
    virtual const std::string toString() const { return getName(); }
  };

#define EVENT_CLASS_TYPE(t) virtual EventType getType() const override { return EventType::##t; }\
                             virtual const char* getName() const override { return #t; }

}