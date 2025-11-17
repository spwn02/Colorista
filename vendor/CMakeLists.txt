cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

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

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)