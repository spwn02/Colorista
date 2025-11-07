#include "Corepch.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Log {

  std::shared_ptr<spdlog::logger> Log::s_logger = nullptr;
  void Log::init()
  {
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/Core.log", true));

    logSinks[0]->set_pattern("%^[%T] %n: %v%$");
    logSinks[1]->set_pattern("[%T] [%l] %n: %v");

    s_logger = std::make_shared<spdlog::logger>("CORE", logSinks.begin(), logSinks.end());
    spdlog::register_logger(s_logger);
    s_logger->set_level(spdlog::level::trace);
    s_logger->flush_on(spdlog::level::trace);

  }

}