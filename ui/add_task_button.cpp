#include <random>
#include <sstream>
#include "ui.hpp"
#include "storage.hpp"
#include "uuid.hpp"

void add_task_button(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 color) {
    if (ImGui::Button("Add Task")) {
        static float posX = 0.0f;
        static float posY = 0.0f;
        float padding = 10.0f;
        float regionWidth = ImGui::GetContentRegionAvail().x;
        ImVec2 cardSize = ImVec2(200, 100);

        if (posX + cardSize.x > regionWidth) {
            posX = 0.0f;
            posY += cardSize.y + padding;
        }

        tasks.push_back(Task{.id = generate_uuid(),
                             .title = titleBuffer,
                             .content = contentBuffer,
                             .position = ImVec2(posX, posY),
                             .color = color,
                             .completed = false});

        posX += cardSize.x + padding;

        titleBuffer[0] = '\0';
        contentBuffer[0] = '\0';

        save_tasks(tasks, "tasks.json");
    }
}