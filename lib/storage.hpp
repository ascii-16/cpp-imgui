#pragma once

#include <vector>
#include "task.hpp"
#include <string>

void save_tasks(const std::vector<Task> &tasks, const std::string &filename = "tasks.json");
bool update_task(std::vector<Task> &tasks, int taskId, const Task &updatedTask);
bool delete_task(std::vector<Task> &tasks, int taskId);
std::vector<Task> load_tasks(const std::string &filename);
