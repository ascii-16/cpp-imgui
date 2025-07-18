#include "storage.hpp"
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void save_tasks(const std::vector<Task> &tasks, const std::string &filename) {
    json j;
    for (const auto &task : tasks) {
        j.push_back({{"id", task.id},
                     {"title", task.title},
                     {"content", task.content},
                     {"position", {task.position.x, task.position.y}},
                     {"color", {task.color.x, task.color.y, task.color.z, task.color.w}},
                     {"completed", task.completed}});
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
    }
}

bool update_task(std::vector<Task> &tasks, int taskId, const Task &updatedTask) {
    for (Task &task : tasks) {
        if (task.id == taskId) {
            task.title = updatedTask.title;
            task.content = updatedTask.content;
            task.position = updatedTask.position;
            task.color = updatedTask.color;
            task.completed = updatedTask.completed;
            save_tasks(tasks);
            return true;
        }
    }
    return false;
}

bool delete_task(std::vector<Task> &tasks, int taskId) {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [taskId](const Task &task) { return task.id == taskId; }),
                tasks.end());
    save_tasks(tasks);
    return true;
}

std::vector<Task> load_tasks(const std::string &filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);
    if (!file.is_open())
        return tasks;

    json j;
    file >> j;
    for (const auto &item : j) {
        Task task;
        task.title = item["title"];
        task.content = item["content"];
        task.position = ImVec2(item["position"][0], item["position"][1]);
        task.color = ImVec4(item["color"][0], item["color"][1], item["color"][2], item["color"][3]);
        task.completed = item["completed"];
        tasks.push_back(task);
    }

    return tasks;
}
