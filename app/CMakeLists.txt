file(GLOB_RECURSE SRCS "*.cpp")
file(GLOB_RECURSE HDRS "*.h")

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

add_compile_definitions(
  GLFW_INCLUDE_NONE
  _CRT_SECURE_NO_WARNINGS
)

target_link_libraries(${PROJECT_NAME} PRIVATE Core)

set_property(TARGET ${PROJECT_NAME} PROPERTY
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
