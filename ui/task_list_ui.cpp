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
    float padding = 12.0f;
    float regionWidth = ImGui::GetContentRegionAvail().x;
    int cardsPerRow = std::max(1, (int) ((regionWidth + padding) / (cardWidth + padding)));

    ImGui::BeginChild("TaskListRegion", ImGui::GetContentRegionAvail(), false,
                      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                          ImGuiWindowFlags_AlwaysUseWindowPadding);

    for (size_t i = 0; i < tasks.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));
        Task &task = tasks[i];

        // Calculate row and column
        int row = i / cardsPerRow;
        int col = i % cardsPerRow;

        if (col > 0) {
            ImGui::SameLine();
            ImGui::SetCursorPosX(col * (cardWidth + padding));
        }

        // Add vertical spacing between rows
        if (row > 0 && col == 0) {
            ImGui::Dummy(ImVec2(0.0f, padding));
        }

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(task.color.x, task.color.y, task.color.z, 0.15f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 0.25f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 8));

        // Get current cursor position for drawing the border
        ImVec2 cardPos = ImGui::GetCursorScreenPos();

        // Draw rounded border for card
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        ImU32 bgColor = ImGui::GetColorU32(task.color);
        draw_list->AddRect(cardPos, ImVec2(cardPos.x + cardWidth, cardPos.y + cardHeight), bgColor, 10.0f, 0, 2.0f);

        // Card content
        ImGui::BeginChild("TaskCard", ImVec2(cardWidth, cardHeight), true,
                          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

        ImGui::TextColored(ImVec4(1, 1, 1, 1), "%s", task.title.c_str());
        ImGui::Spacing();
        ImGui::TextWrapped("%s", task.content.c_str());

        ImGui::Dummy(ImVec2(0.0f, 8.0f));

        // Footer row with checkbox and delete icon
        ImGui::BeginGroup();
        if (ImGui::Checkbox("Done", &task.completed)) {
            update_task(tasks, task.id, task);
        }
        ImGui::EndGroup();

        ImGui::SameLine();
        ImGui::SetCursorPosX(cardWidth - 24);
        delete_button(tasks, task.id);

        ImGui::EndChild();

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);
        ImGui::PopID();
    }

    ImGui::EndChild();
}
