file(GLOB_RECURSE SRCS "*.cpp")
file(GLOB_RECURSE HDRS "*.h")

add_library(Core STATIC ${SRCS} ${HDRS})

# Match VS filters to directory structure on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS} ${HDRS})

add_compile_definitions(
  "GLFW_INCLUDE_NONE"
  "CORE_DEBUG"
  "PLATFORM_WINDOWS"
)

target_precompile_headers(Core PUBLIC "Corepch.h")

target_include_directories(Core PUBLIC "." "src")
