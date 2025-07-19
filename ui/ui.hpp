#pragma once

#include <vector>
#include "task.hpp"

void render_task_list(std::vector<Task> &tasks, float cardWidth = 200.0f, float cardHeight = 100.0f);
void add_task_button(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 color);