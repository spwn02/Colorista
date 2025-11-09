file(GLOB_RECURSE SRCS "*.cpp")
file(GLOB_RECURSE HDRS "*.h")

add_library(Core STATIC ${SRCS} ${HDRS})

# Match VS filters to directory structure on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS} ${HDRS})

target_compile_definitions(Core PUBLIC
  CORE_DEBUG
  _CRT_SECURE_NO_WARNINGS
  NOMINMAX
)

target_precompile_headers(Core PUBLIC "Corepch.h")

target_include_directories(Core PUBLIC "${CMAKE_SOURCE_DIR}/core" "src")
