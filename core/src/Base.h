#pragma once

#ifdef _WIN32
  #define CORE_PLATFORM_WINDOWS
#endif

#ifdef linux
  #define CORE_PLATFORM_LINUX
#endif

#ifdef CORE_DEBUG
  #ifdef CORE_PLATFORM_WINDOWS
    #define CORE_DEBUGBREAK() __debugbreak()
  #elifdef CORE_PLATFORM_LINUX
    #include <signal.h>
    #define CORE_DEBUGBREAK() raise(SIGTRAP)
  #else
    #error "debugbreak is not supported on the current platform yet!"
  #endif
  #define CORE_ENABLE_ASSERTS
#else
  #define DebugBreak()
#endif

#define CORE_STRINGIFY(x) #x

#define BIT(x) (1 << x)

#define CORE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
