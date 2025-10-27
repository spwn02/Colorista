#pragma once

#include "Event.h"

#include <sstream>

namespace Events {

  struct MouseMovedEvent : Event
  {
    double x, y;

    explicit MouseMovedEvent(double x, double y)
      : x(x), y(y) {
    }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseMovedEvent: " << x << ", " << y;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
  };

  struct MouseScrolledEvent : Event
  {
    double x, y;

    explicit MouseScrolledEvent(double x, double y)
      : x(x), y(y) {
    }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseScrolledEvent: " << x << ", " << y;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
  };

  struct MouseButtonEvent : Event
  {
    int32_t button;

    explicit MouseButtonEvent(int32_t button)
      : button(button) {
    }
  };

  struct MouseButtonPressedEvent : MouseButtonEvent
  {
    int32_t mods;

    MouseButtonPressedEvent(int32_t button, int32_t mods)
      : MouseButtonEvent(button), mods(mods) {
    }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseButtonPressedEvent: " << button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  struct MouseButtonReleasedEvent : MouseButtonEvent
  {
    MouseButtonReleasedEvent(int32_t button)
      : MouseButtonEvent(button) {
    }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseButtonReleasedEvent: " << button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
  };

}