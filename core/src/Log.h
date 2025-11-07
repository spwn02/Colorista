#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Base.h"

namespace Log {

  class Log
  {
  public:
    Log() = default;
    ~Log() = default;

    static void init();
    static std::shared_ptr<spdlog::logger>& get() { return s_logger; }
  private:
    static std::shared_ptr<spdlog::logger> s_logger;
  };

  template<typename T, typename... Types>
  static inline void Trace(T message, Types... args)
  {
    Log::get()->trace(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  static inline void Info(T message, Types... args)
  {
    Log::get()->info(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  static inline void Warn(T message, Types... args)
  {
    Log::get()->warn(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  static inline void Error(T message, Types... args)
  {
    Log::get()->error(spdlog::fmt_lib::runtime(message), args...);
  }

  #ifdef CORE_ENABLE_ASSERTS
    template<typename T, typename... Types>
    static inline void Assert(bool condition, T message, Types... args)
    {
      if (!condition)
      {
        Error(message, args...);
        CORE_DEBUGBREAK();
      }
    };

    static inline void Assert(bool condition)
    {
      if (!condition)
      {
        Error("Assertion '{0}' failed.", CORE_STRINGIFY(condition));
        CORE_DEBUGBREAK();
      }
    };
  #else
    template<typename T, typename... Types>
    static inline void Assert(bool condition, T message, Types... args) {}
    static inline void Assert(bool condition) {}
  #endif

  template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
  inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
  {
    return os << glm::to_string(vector);
  }

  template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
  inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
  {
    return os << glm::to_string(matrix);
  }

  template<typename OStream, typename T, glm::qualifier Q>
  inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
  {
    return os << glm::to_string(quaternion);
  }

}