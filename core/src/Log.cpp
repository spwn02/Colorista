#include "Log.h"

namespace Log {

  std::shared_ptr<spdlog::logger> Log::s_logger = nullptr;
  bool Log::s_running = false;

  void Log::init()
  {
    if (s_running) return;

    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_logger = spdlog::stdout_color_mt("Core");
    s_logger->set_level(spdlog::level::trace);

    s_running = true;
  }

}