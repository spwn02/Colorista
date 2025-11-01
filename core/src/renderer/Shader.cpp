#include "Corepch.h"

#include "Shader.h"
#include "renderer/RendererAPI.h"

#include "platform/OpenGL/OpenGLShader.h"

namespace Renderer {

  ComputeShader* ComputeShader::create(const std::filesystem::path& path)
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      return new OpenGLComputeShader(path);
    default:
      return nullptr;
    }
  }

  GraphicsShader* GraphicsShader::create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      return new OpenGLGraphicsShader(vertexPath, fragmentPath);
    default:
      return nullptr;
    }
  }

  int32_t Shader::getUniformLocation(const std::string& name) const
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      return OpenGLUniformLocation(m_handle, name);
    default:
      return 0;
    }
  }

  void Shader::setUniform1f(const std::string& name, float x) const
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      OpenGLUniform1f(getUniformLocation(name), x);
      break;
    default:
      break;
    }
  }

  void Shader::setUniform2f(const std::string& name, float x, float y) const
  {
    switch (RendererAPI::getAPI())
    {
    case OpenGL:
      OpenGLUniform2f(getUniformLocation(name), x, y);
      break;
    default:
      break;
    }
  }

}