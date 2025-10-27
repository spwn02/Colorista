#include "Corepch.h"

#include "OpenGLShader.h"

#include "Utils.h"

namespace Renderer {

  // ----------------------------------------
  //              Compute Shader
  // ----------------------------------------
  OpenGLComputeShader::OpenGLComputeShader(const std::filesystem::path& path)
  {
    generate(path);
  }

  bool OpenGLComputeShader::generate(const std::filesystem::path& path)
  {
    std::string shaderSource = Core::readTextFile(path);

    GLuint shaderHandle = glCreateShader(GL_COMPUTE_SHADER);

    const GLchar* source = (const GLchar*)shaderSource.c_str();
    glShaderSource(shaderHandle, 1, &source, 0);

    glCompileShader(shaderHandle);

    GLint isCompiled = 0;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(shaderHandle, maxLength, &maxLength, &infoLog[0]);

      Log::Error(infoLog.data());

      glDeleteShader(shaderHandle);
      return false;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, shaderHandle);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

      Log::Error(infoLog.data());

      glDeleteProgram(program);
      glDeleteShader(shaderHandle);

      return false;
    }

    glDetachShader(program, shaderHandle);
    m_handle = program;
    return true;
  }

  OpenGLComputeShader::~OpenGLComputeShader()
  {
    unbind();
    glDeleteProgram(m_handle);
  }

  void OpenGLComputeShader::bind() const
  {
    glUseProgram(m_handle);
  }

  void OpenGLComputeShader::unbind() const
  {
    glUseProgram(0);
  }

  void OpenGLComputeShader::reload(const std::filesystem::path& path)
  {
    uint32_t prevShader = m_handle;
    bool success = generate(path);

    if (success) glDeleteProgram(prevShader);
  }

  // ----------------------------------------
  //              Graphics Shader
  // ----------------------------------------
  OpenGLGraphicsShader::OpenGLGraphicsShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
  {
    generate(vertexPath, fragmentPath);
  }

  OpenGLGraphicsShader::~OpenGLGraphicsShader()
  {
    unbind();
    glDeleteProgram(m_handle);
  }

  void OpenGLGraphicsShader::bind() const
  {
    glUseProgram(m_handle);
  }

  void OpenGLGraphicsShader::unbind() const
  {
    glUseProgram(0);
  }

  bool OpenGLGraphicsShader::generate(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
  {
    std::string vertexShaderSource = Core::readTextFile(vertexPath);
    std::string fragmentShaderSource = Core::readTextFile(fragmentPath);

    // Vertex shader

    GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* source = (const GLchar*)vertexShaderSource.c_str();
    glShaderSource(vertexShaderHandle, 1, &source, 0);

    glCompileShader(vertexShaderHandle);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetShaderiv(vertexShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(vertexShaderHandle, maxLength, &maxLength, &infoLog[0]);

      Log::Error(infoLog.data());

      glDeleteShader(vertexShaderHandle);
      return false;
    }

    // Fragment shader

    GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

    source = (const GLchar*)fragmentShaderSource.c_str();
    glShaderSource(fragmentShaderHandle, 1, &source, 0);

    glCompileShader(fragmentShaderHandle);

    isCompiled = 0;
    glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetShaderiv(fragmentShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(fragmentShaderHandle, maxLength, &maxLength, &infoLog[0]);

      Log::Error(infoLog.data());

      glDeleteShader(fragmentShaderHandle);
      return false;
    }

    // Program linking

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShaderHandle);
    glAttachShader(program, fragmentShaderHandle);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

      Log::Error(infoLog.data());

      glDeleteProgram(program);
      glDeleteShader(vertexShaderHandle);
      glDeleteShader(fragmentShaderHandle);

      return false;
    }

    glDetachShader(program, vertexShaderHandle);
    glDetachShader(program, fragmentShaderHandle);
    m_handle = program;
    return true;
  }

  void OpenGLGraphicsShader::reload(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
  {
    uint32_t prevShader = m_handle;
    bool success = generate(vertexPath, fragmentPath);

    if (success) glDeleteProgram(prevShader);
  }

  // ----------------------------------------
  //                Uniforms
  // ----------------------------------------
  int32_t OpenGLUniformLocation(uint32_t program, const std::string& name)
  {
    return glGetUniformLocation(program, name.c_str());
  }

  void OpenGLUniform1f(uint32_t location, float x)
  {
    glUniform1f(location, x);
  }

  void OpenGLUniform2f(uint32_t location, float x, float y)
  {
    glUniform2f(location, x, y);
  }

}