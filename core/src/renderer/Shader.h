#pragma once

#include <filesystem>

namespace Renderer {

  uint32_t createComputeShader(const std::filesystem::path& path);
  uint32_t reloadComputeShader(uint32_t shaderHandle, const std::filesystem::path& path);

  uint32_t createGraphicsShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
  uint32_t reloadGraphicsShader(uint32_t shaderHandle, const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

}