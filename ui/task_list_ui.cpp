#include "ui.hpp"
#include "storage.hpp"

void render_task_list(std::vector<Task> &tasks, float cardWidth, float cardHeight) {
    ImGui::BeginChild("TaskListRegion", ImGui::GetContentRegionAvail(), false,
                      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                          ImGuiWindowFlags_AlwaysUseWindowPadding);

    for (size_t i = 0; i < tasks.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));
        Task &task = tasks[i];

        ImGui::SetCursorPos(task.position);

        ImGui::PushStyleColor(ImGuiCol_ChildBg, task.color);

        ImGui::BeginChild("TaskCard", ImVec2(cardWidth, cardHeight), true, ImGuiWindowFlags_NoMove);
        ImGui::Text("%s", task.title.c_str());
        ImGui::Separator();
        ImGui::TextWrapped("%s", task.content.c_str());
        ImGui::Checkbox("Done", &task.completed);

        if (ImGui::Button("Delete")) {
            delete_task(tasks, task.id);
        }

        ImGui::EndChild();

        ImGui::PopStyleColor();
        ImGui::PopID();
    }

    ImGui::EndChild();
}
