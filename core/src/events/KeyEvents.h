#pragma once

#include "Event.h"

#include <sstream>

namespace Events {

  struct KeyEvent : Event
  {
    int32_t keyCode;

    explicit KeyEvent(int32_t keyCode)
      : keyCode(keyCode) {
    }
  };

  struct KeyPressedEvent : KeyEvent
  {
    int32_t scanCode, mods, repeatCount;

    explicit KeyPressedEvent(int32_t keyCode, int32_t scanCode, int32_t mods, int32_t repeatCount)
      : KeyEvent(keyCode), scanCode(scanCode), mods(mods), repeatCount(repeatCount) {
    };

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
  };

  struct KeyReleasedEvent : KeyEvent
  {
    int32_t scanCode, mods;

    explicit KeyReleasedEvent(int32_t keyCode, int32_t scanCode, int32_t mods)
      : KeyEvent(keyCode), scanCode(scanCode), mods(mods) {
    };

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << keyCode;
      return ss.str();
    };

    EVENT_CLASS_TYPE(KeyReleased)
  };

  struct KeyTypedEvent : KeyEvent
  {
    explicit KeyTypedEvent(int32_t keyCode)
      : KeyEvent(keyCode) {
    }

    const std::string toString() const override
    {
      std::stringstream ss;
      ss << "KeyTypedEvent: " << keyCode;
      return ss.str();
    };

    EVENT_CLASS_TYPE(KeyTyped)
  };

}