#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "Log.h"

namespace Core {

  static std::string readTextFile(const std::filesystem::path& path)
  {
    std::ifstream file(path);

    Log::Assert(file.is_open(), "Failed to open file: {0}", path.string());

    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    return contentStream.str();
  }

}