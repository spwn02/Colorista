#include "Shader.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Log.h"

namespace Renderer {

  static std::string readTextFile(const std::filesystem::path& path)
  {
    std::ifstream file(path);

    Log::Assert(file.is_open(), "Failed to open file: {0}", path.string());

    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    return contentStream.str();
  }

  uint32_t createComputeShader(const std::filesystem::path& path)
  {
    std::string shaderSource = readTextFile(path);

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
      return -1;
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

      return -1;
    }

    glDetachShader(program, shaderHandle);
    return program;
  }

  uint32_t reloadComputeShader(uint32_t shaderHandle, const std::filesystem::path& path)
  {
    uint32_t newShaderHandle = createComputeShader(path);

    // Return old shader if compilation failed
    if (newShaderHandle == -1)
      return shaderHandle;

    glDeleteProgram(shaderHandle);
    return newShaderHandle;
  }

  uint32_t createGraphicsShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
  {
    std::string vertexShaderSource = readTextFile(vertexPath);
    std::string fragmentShaderSource = readTextFile(fragmentPath);

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
      return -1;
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
      return -1;
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

      return -1;
    }

    glDetachShader(program, vertexShaderHandle);
    glDetachShader(program, fragmentShaderHandle);
    return program;
  }

  uint32_t reloadGraphicsShader(uint32_t shaderHandle, const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
  {
    uint32_t newShaderHandle = createGraphicsShader(vertexPath, fragmentPath);

    // Return old shader if compilation failed
    if (newShaderHandle == -1)
      return shaderHandle;

    glDeleteProgram(shaderHandle);
    return newShaderHandle;
  }

}