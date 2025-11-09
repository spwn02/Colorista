cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# General
find_package(OpenGL REQUIRED)

add_subdirectory(glm)
add_subdirectory(spdlog)
target_compile_definitions(spdlog PRIVATE
  _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
  _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
)

# GLFW
if (LINUX)
set(GLFW_BUILD_X11      ON CACHE BOOL "Disable X11 support"        FORCE)
set(GLFW_BUILD_WAYLAND  OFF  CACHE BOOL "Enable Wayland support"     FORCE)
set(GLFW_USE_EGL        ON  CACHE BOOL "Enable EGL instead of GLX"  FORCE)
endif()

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

# Glad
add_library(glad "glad/src/glad.c")
target_include_directories(glad PUBLIC "glad/include")

# ImGui
set(PHDR "imgui/imgui.h" "imgui/imgui_internal.h")
set(HDRS "imgui/imstb_rectpack.h" "imgui/imstb_textedit.h" "imgui/imstb_truetype.h")

add_library(imgui STATIC
  "imgui/imgui.cpp"
  "imgui/imgui_demo.cpp"
  "imgui/imgui_draw.cpp"
  "imgui/imgui_tables.cpp"
  "imgui/imgui_widgets.cpp"
  ${PHDR}
  ${HDRS}
)
target_sources(imgui PRIVATE
  "imgui/backends/imgui_impl_glfw.cpp"
  "imgui/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(imgui PUBLIC "imgui" "imgui/backends")
target_compile_definitions(imgui PUBLIC
  IMGUI_DISABLE_INCLUDE_IMCONFIG_H
  IMGUI_IMPL_OPENGL_LOADER_GLAD
)
target_link_libraries(imgui PUBLIC glfw)

# stb
add_library(stb "stb/stb_image.cpp")
target_include_directories(stb PUBLIC "stb")

target_compile_definitions(Core PUBLIC
  GLFW_INCLUDE_NONE
  GLFW_PLATFORM_X11
  IMGUI_IMPL_OPENGL_LOADER_CUSTOM
)

# Linking
if (WIN32)
  message(STATUS "Linking vendor libraries for Windows")
  target_link_libraries(Core PUBLIC
  opengl32
  )
elseif (LINUX)
find_package(X11 REQUIRED)

message(STATUS "Linking vendor libraries for Linux")
  target_link_libraries(Core PUBLIC
  dl
  pthread
  X11::X11
  X11::Xrandr
  X11::Xi
  X11::Xcursor
  X11::Xinerama
  X11::Xxf86vm
  )
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

target_link_libraries(Core PUBLIC
  OpenGL::GL
  glad
  glfw
  glm
  imgui
  spdlog
  stb
)