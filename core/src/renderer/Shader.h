#pragma once

#include <filesystem>
#include <stdint.h>

namespace Renderer {

  class Shader
  {
  public:
    uint32_t getHandle() { return m_handle; }

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    void setUniform1f(const std::string& name, float x) const;
    void setUniform2f(const std::string& name, float x, float y) const;
    int32_t getUniformLocation(const std::string& name) const;
  protected:
    uint32_t m_handle = 0;
  };

  // ----------------------------------------
  //                 Shaders
  // ----------------------------------------
  class ComputeShader : public Shader
  {
  public:
    virtual ~ComputeShader() = default;

    virtual bool generate(const std::filesystem::path& path) = 0;
    virtual void reload(const std::filesystem::path& path) = 0;

    static ComputeShader* create(const std::filesystem::path& path);
  };

  class GraphicsShader : public Shader
  {
  public:
    virtual ~GraphicsShader() = default;

    virtual bool generate(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) = 0;
    virtual void reload(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) = 0;

    static GraphicsShader* create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
  };

}