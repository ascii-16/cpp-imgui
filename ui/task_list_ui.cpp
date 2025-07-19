#include "ui.hpp"
#include "storage.hpp"
#include "image.hpp"

/**
 * @brief Renders a delete button as an icon and handles task deletion logic.
 *
 * This function displays a delete icon for a task. When the icon is clicked, the corresponding task is removed
 * from the provided tasks vector and persistent storage is updated.
 *
 * @param tasks Reference to the vector of Task objects.
 * @param task_id The unique identifier of the task to be deleted.
 */
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

/**
 * @brief Renders the list of tasks as interactive cards in a grid layout.
 *
 * This function iterates over the provided tasks vector and displays each task as a card with its title, content,
 * completion status, and a delete button. The layout is responsive to the available region width. Task completion
 * and deletion are handled interactively, and changes are persisted.
 *
 * @param tasks Reference to the vector of Task objects to display and manage.
 * @param cardWidth The width of each task card in the UI.
 * @param cardHeight The height of each task card in the UI.
 */
void render_task_list(std::vector<Task> &tasks, float cardWidth, float cardHeight) {
    float padding = 12.0f;
    float regionWidth = ImGui::GetContentRegionAvail().x;
    float posX = 0.0f, posY = 0.0f;

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

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(task.color.x, task.color.y, task.color.z, 0.15f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 0.25f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 8));

        // Rounded border for card
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        ImU32 bgColor = ImGui::GetColorU32(task.color);
        draw_list->AddRect(cardPos, ImVec2(cardPos.x + cardWidth, cardPos.y + cardHeight), bgColor, 10.0f, 0, 2.0f);
        ImGui::SetCursorScreenPos(ImVec2(cardPos.x + 4, cardPos.y + 4));

        // Card
        ImGui::BeginChild("TaskCard", ImVec2(cardWidth - 8, cardHeight - 8), true,
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

        // End card
        ImGui::EndChild();

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);

        posX += cardWidth + padding;
        ImGui::PopID();
    }

    ImGui::EndChild();
}
