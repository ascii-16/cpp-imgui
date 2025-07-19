#include "ui.hpp"
#include "storage.hpp"
#include "image.hpp"

void delete_button(std::vector<Task> &tasks, std::string task_id) {
    GLuint iconTex = LoadPNGTexture("assets/icons/delete.png");
    ImVec2 iconSize = ImVec2((float) 18, (float) 18);
    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::Image((ImTextureID) (intptr_t) iconTex, iconSize);

    // Create invisible button over the image
    ImGui::SetCursorScreenPos(pos);
    if (ImGui::InvisibleButton("delete_button", iconSize)) {
        delete_task(tasks, task_id);
    }
}

void render_task_list(std::vector<Task> &tasks, float cardWidth, float cardHeight) {
    float padding = 10.0f;
    float regionWidth = ImGui::GetContentRegionAvail().x;
    float posX = 0.0f;
    float posY = 0.0f;

    ImVec2 origin = ImGui::GetCursorScreenPos();

    ImGui::BeginChild("TaskListRegion", ImGui::GetContentRegionAvail(), false,
                      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                          ImGuiWindowFlags_AlwaysUseWindowPadding);

    for (size_t i = 0; i < tasks.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));
        Task &task = tasks[i];

        if (posX + cardWidth > regionWidth) {
            posX = 0.0f;
            posY += cardHeight + padding;
        }

        ImVec2 cardPos = ImVec2(origin.x + posX, origin.y + posY);

        ImGui::SetCursorScreenPos(cardPos);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, task.color);

        ImGui::BeginChild("TaskCard", ImVec2(cardWidth, cardHeight), true, ImGuiWindowFlags_NoMove);
        ImGui::Text("%s", task.title.c_str());
        ImGui::Separator();
        ImGui::TextWrapped("%s", task.content.c_str());
        ImGui::Checkbox("Done", &task.completed);

        delete_button(tasks, task.id);

        ImGui::EndChild();
        ImGui::PopStyleColor();

        posX += cardWidth + padding;

        ImGui::PopID();
    }

    ImGui::EndChild();
}
