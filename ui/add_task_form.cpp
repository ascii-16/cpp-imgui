#include <random>
#include <sstream>
#include "ui.hpp"
#include "storage.hpp"
#include "uuid.hpp"

/**
 * @brief Renders the form UI for adding a new task and handles its submission logic.
 *
 * This function displays input fields for the task title, content, and color. When the user submits the form,
 * it creates a new Task object, assigns a unique UUID, and appends it to the provided tasks vector. The form
 * fields are cleared after submission, and the updated task list is persisted to storage.
 *
 * @param tasks Reference to the vector of Task objects to which the new task will be added.
 * @param titleBuffer Character buffer for the task title input field (mutable).
 * @param contentBuffer Character buffer for the task content input field (mutable).
 * @param color The color associated with the new task.
 */
void add_task_form(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 &color) {

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 0.95f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));

    ImGui::BeginChild("AddTaskForm", ImVec2(0, 370), true, ImGuiWindowFlags_NoScrollbar);

    ImGui::PushFont(nullptr);
    ImGui::Text("✨ Create New Task");
    ImGui::PopFont();

    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 10));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.18f, 0.18f, 0.18f, 1.0f));

    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Title");
    ImGui::SetNextItemWidth(-1); // Make Full width
    ImGui::InputTextWithHint("##Title", "Enter task title...", titleBuffer, IM_ARRAYSIZE(titleBuffer));

    ImGui::Spacing();

    // Content input
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Description");
    ImGui::SetNextItemWidth(-1);
    ImGui::InputTextMultiline("##Content", contentBuffer, IM_ARRAYSIZE(contentBuffer), ImVec2(-1, 80),
                              ImGuiInputTextFlags_None);

    ImGui::Spacing();

    // Color picker
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Color Theme");
    ImGui::SetNextItemWidth(120);
    ImGui::ColorEdit4("##Color", (float *) &color,
                      ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar);

    ImGui::SameLine();

    // Show color preview with name
    ImGui::PushStyleColor(ImGuiCol_Button, color);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x * 1.1f, color.y * 1.1f, color.z * 1.1f, color.w));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x * 0.9f, color.y * 0.9f, color.z * 0.9f, color.w));
    ImGui::Button("Color Preview", ImVec2(200, 0));
    ImGui::PopStyleColor(3);

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    float buttonWidth = 120.0f;
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float buttonPosX = 20.0f;

    ImGui::SetCursorPosX(buttonPosX);

    // Add Task button
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 12));

    // Gradient-like button colors
    ImVec4 buttonColor = ImVec4(0.2f, 0.6f, 0.8f, 1.0f);
    ImVec4 buttonHovered = ImVec4(0.25f, 0.65f, 0.85f, 1.0f);
    ImVec4 buttonActive = ImVec4(0.15f, 0.55f, 0.75f, 1.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonHovered);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonActive);

    bool addPressed = ImGui::Button("✅ Add Task", ImVec2(buttonWidth, 0));

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);

    // Handle form submission
    if (addPressed) {
        // Validation
        if (strlen(titleBuffer) == 0) {
            // Validation failed
            // TODO: Show validation error messages
            return;
        } else {
            tasks.insert(tasks.begin(), Task{.id = generate_uuid(),
                                             .title = std::string(titleBuffer),
                                             .content = std::string(contentBuffer),
                                             .color = color,
                                             .completed = false});

            titleBuffer[0] = '\0';
            contentBuffer[0] = '\0';

            color = ImVec4(0.3f, 0.7f, 0.9f, 1.0f);

            save_tasks(tasks, "tasks.json");
        }
    }

    ImGui::EndChild();

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);
}
