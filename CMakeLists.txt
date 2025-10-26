# Configuration
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Colorista VERSION 1.0)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Core library
file(GLOB_RECURSE SRCS "core/*.cpp")
file(GLOB_RECURSE HDRS "core/*.h")

add_library(Core STATIC ${SRCS} ${HDRS})

set_target_properties(Core PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_compile_definitions(Core PRIVATE
  "GLFW_INCLUDE_NONE"
  "CORE_DEBUG"
)

target_include_directories(Core PUBLIC "core" "core/src")

# App
file(GLOB_RECURSE SRCS "app/*.cpp")
file(GLOB_RECURSE HDRS "app/*.h")

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

target_link_libraries(${PROJECT_NAME} PUBLIC Core)

target_compile_definitions(${PROJECT_NAME} PUBLIC
  "_CRT_SECURE_NO_WARNINGS"
)

add_subdirectory("vendor")