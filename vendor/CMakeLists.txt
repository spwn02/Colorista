cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

find_package(OpenGL REQUIRED)

# General
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(spdlog)
target_compile_definitions(spdlog PRIVATE
  _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
  _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
)

# Glad
add_library(glad "glad/src/glad.c")
target_include_directories(glad PUBLIC "glad/include")

# ImGui
set(PHDR "imgui/imgui.h" "imgui/imgui_internal.h")
set(HDRS "imgui/imstb_rectpack.h" "imgui/imstb_textedit" "imgui/imstb_truetype.h")

add_library(imgui
  "imgui/imgui.cpp"
  "imgui/imgui_demo.cpp"
  "imgui/imgui_draw.cpp"
  "imgui/imgui_tables.cpp"
  "imgui/imgui_widgets.cpp"
  ${PHDR}
  ${HDRS}
)
target_include_directories(imgui PUBLIC "imgui")
target_compile_definitions(imgui PUBLIC
  IMGUI_DISABLE_INCLUDE_IMCONFIG_H
)

# stb
add_library(stb "stb/stb_image.cpp")
target_include_directories(stb PUBLIC "stb")

# Linking
target_link_libraries(Core PUBLIC
  OpenGL::GL
  opengl32.lib
  glad
  glfw
  glm
  imgui
  spdlog
  stb
)