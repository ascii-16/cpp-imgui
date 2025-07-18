#include "storage.hpp"
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void save_tasks(const std::vector<Task> &tasks, const std::string &filename) {
    json j;
    for (const auto &task : tasks) {
        j.push_back({
            {"title", task.title},
            {"content", task.content},
            {"position", {task.position.x, task.position.y}},
            {"color", {task.color.x, task.color.y, task.color.z, task.color.w}},
            {"completed", task.completed}
        });
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
    }
}

std::vector<Task> load_tasks(const std::string &filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);
    if (!file.is_open()) return tasks;

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
