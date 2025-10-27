#pragma once

#include "renderer/Shader.h"

namespace Renderer {

  class OpenGLComputeShader : public ComputeShader
  {
  public:
    OpenGLComputeShader(const std::filesystem::path& path);
    virtual ~OpenGLComputeShader() override;

    void bind() const override;
    void unbind() const override;

    bool generate(const std::filesystem::path& path) override;
    void reload(const std::filesystem::path& path) override;
  };

  class OpenGLGraphicsShader : public GraphicsShader
  {
  public:
    OpenGLGraphicsShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
    virtual ~OpenGLGraphicsShader() override;

    void bind() const override;
    void unbind() const override;

    bool generate(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) override;
    virtual void reload(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) override;
  };

  int32_t OpenGLUniformLocation(uint32_t program, const std::string& name);
  void OpenGLUniform1f(uint32_t location, float x);
  void OpenGLUniform2f(uint32_t location, float x, float y);
}