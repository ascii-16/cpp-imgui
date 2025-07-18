#include "ui.hpp"
#include "storage.hpp"
#include "image.hpp"

void render_task_list(std::vector<Task> &tasks, float cardWidth, float cardHeight) {
    GLuint iconTex = LoadPNGTexture("assets/icons/delete.png");

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

        // Delete Button
        ImVec2 iconSize = ImVec2((float) 18, (float) 18);

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::Image((ImTextureID) (intptr_t) iconTex, iconSize);

        // Create invisible button over the image
        ImGui::SetCursorScreenPos(pos);
        if (ImGui::InvisibleButton("delete_button", iconSize)) {
            delete_task(tasks, task.id);
        }

        ImGui::EndChild();

        ImGui::PopStyleColor();
        ImGui::PopID();
    }

    ImGui::EndChild();
}
