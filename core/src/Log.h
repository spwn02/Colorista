#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace Log {

  class Log
  {
  public:
    Log() = default;
    ~Log() = default;

    static void init();
    static std::shared_ptr<spdlog::logger>& get() { return s_logger; }
  protected:
    static std::shared_ptr<spdlog::logger> s_logger;
  private:
    static bool s_running;
  };

  template<typename T, typename... Types>
  inline void Trace(T message, Types... args)
  {
    Log::get()->trace(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  inline void Info(T message, Types... args)
  {
    Log::get()->info(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  inline void Warn(T message, Types... args)
  {
    Log::get()->warn(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  inline void Error(T message, Types... args)
  {
    Log::get()->error(spdlog::fmt_lib::runtime(message), args...);
  }

  template<typename T, typename... Types>
  inline void Assert(bool condition, T message, Types... args)
  {
    if (!condition)
    {
      Error(message, args...);
      __debugbreak();
      assert(false);
    }
  };

}