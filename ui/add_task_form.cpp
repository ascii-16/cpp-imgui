#include <random>
#include <sstream>
#include "ui.hpp"
#include "storage.hpp"
#include "uuid.hpp"

void add_task_form(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 color) {
    ImGui::InputText("Title", titleBuffer, IM_ARRAYSIZE(titleBuffer));
    ImGui::InputTextMultiline("Content", contentBuffer, IM_ARRAYSIZE(contentBuffer));
    ImGui::ColorEdit4("Color", (float *) &color);
    if (ImGui::Button("Add Task")) {
        tasks.push_back(Task{
            .id = generate_uuid(), .title = titleBuffer, .content = contentBuffer, .color = color, .completed = false});

        titleBuffer[0] = '\0';
        contentBuffer[0] = '\0';

        save_tasks(tasks, "tasks.json");
    }
}