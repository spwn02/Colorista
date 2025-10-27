#include "Corepch.h"

#include "OpenGLSetup.h"

namespace Renderer {

  bool OpenGLSetup::s_initialized = false;
  bool OpenGLSetup::s_gladLoaded = false;

  void OpenGLSetup::setup()
  {
    Log::Assert(glfwInit(), "Failed to Initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef CORE_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    glfwSetErrorCallback([](int code, const char* message) {
      Log::Assert(false, "GLFW error({0}): {1}", code, message);
      });

    s_initialized = true;
  }

  void OpenGLSetup::loadGlad()
  {
    gladLoadGL();

    Log::Assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD!");

    s_gladLoaded = true;
  }

  void OpenGLSetup::shutdown()
  {
    glfwTerminate();

    s_initialized = false;
    s_gladLoaded = false;
  }

}