#pragma once

#include <vector>
#include "task.hpp"
#include <string>

void save_tasks(const std::vector<Task> &tasks, const std::string &filename);
std::vector<Task> load_tasks(const std::string &filename);
