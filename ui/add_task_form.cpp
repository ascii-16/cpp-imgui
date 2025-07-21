#include <iostream>
#include <random>
#include <sstream>
#include "ui.hpp"
#include "storage.hpp"
#include "uuid.hpp"
#include "image.hpp"


void add_task_form(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 &color) {
    static bool isTitleEmpty = false;

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 0.95f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));

    ImGui::BeginChild("AddTaskForm", ImVec2(0, 370), true, ImGuiWindowFlags_NoScrollbar);

    ImGui::Text("Create New Task");
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
    if (isTitleEmpty) {
        ImGui::SetWindowFontScale(0.85f);
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Title is required");
        ImGui::SetWindowFontScale(1.0f);
    }

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

    // Set button position
    float buttonPosX = 20.0f;
    ImGui::SetCursorPosX(buttonPosX);

    bool addPressed = button_with_icon("assets/icons/plus.png", "Add Task");

    // Handle form submission
    if (addPressed) {
        // Validation
        if (strlen(titleBuffer) == 0) {
            // Validation failed
            isTitleEmpty = true;
        } else {
            tasks.insert(tasks.begin(), Task{.id = generate_uuid(),
                                             .title = std::string(titleBuffer),
                                             .content = std::string(contentBuffer),
                                             .color = color,
                                             .completed = false});

            titleBuffer[0] = '\0';
            contentBuffer[0] = '\0';
            isTitleEmpty = false;
            color = ImVec4(0.3f, 0.7f, 0.9f, 1.0f);

            save_tasks(tasks, "tasks.json");
        }
    }

    ImGui::EndChild();
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);
}
