#pragma once

#include <string>
#include "imgui.h"

struct Task
{
  std::string title;
  std::string content;
  ImVec2 position;
  ImVec4 color;
  bool completed;
};