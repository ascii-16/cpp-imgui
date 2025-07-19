#include <random>
#include <sstream>
#include "ui.hpp"
#include "storage.hpp"
#include "uuid.hpp"

void add_task_button(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 color) {
    if (ImGui::Button("Add Task")) {
        tasks.push_back(Task{
            .id = generate_uuid(), .title = titleBuffer, .content = contentBuffer, .color = color, .completed = false});

        titleBuffer[0] = '\0';
        contentBuffer[0] = '\0';

        save_tasks(tasks, "tasks.json");
    }
}