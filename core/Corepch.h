#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <print>
#include <filesystem>
#include <fstream>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Base.h"

#ifdef CORE_PLATFORM_WINDOWS
  #include <Windows.h>
#endif