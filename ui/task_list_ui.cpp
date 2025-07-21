#include "ui.hpp"
#include "storage.hpp"
#include "image.hpp"
#include "mode.hpp"

#define WHITE ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
#define BLACK ImVec4(1.0f, 1.0f, 1.0f, 1.0f)

void delete_button(std::vector<Task> &tasks, std::string task_id) {
    GLuint iconTex = LoadPNGTexture("assets/icons/delete.png");
    ImVec2 iconSize = ImVec2(20.0f, 20.0f);
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // Hover animation state
    static std::unordered_map<std::string, float> deleteButtonHover;
    float &hoverAmount = deleteButtonHover[task_id];

    bool isHovered = ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + iconSize.x, pos.y + iconSize.y));
    hoverAmount += (isHovered ? 1.0f : -1.0f) * ImGui::GetIO().DeltaTime * 8.0f;
    hoverAmount = std::max(0.0f, std::min(1.0f, hoverAmount));

    // Animated hover background
    if (hoverAmount > 0.01f) {
        ImDrawList *drawList = ImGui::GetWindowDrawList();
        float radius = 12.0f + hoverAmount * 3.0f;
        ImU32 hoverColor = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.4f, 0.4f, 0.2f * hoverAmount));
        drawList->AddCircleFilled(ImVec2(pos.x + iconSize.x * 0.5f, pos.y + iconSize.y * 0.5f), radius, hoverColor);
    }

    // Icon with opacity based on hover
    float iconAlpha = 0.6f + hoverAmount * 0.4f;
    ImGui::SetCursorScreenPos(pos);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, iconAlpha);
    ImGui::Image((ImTextureID) (intptr_t) iconTex, iconSize);
    ImGui::PopStyleVar();

    // Invisible button
    ImGui::SetCursorScreenPos(pos);
    if (ImGui::InvisibleButton(("delete_" + task_id).c_str(), iconSize)) {
        delete_task(tasks, task_id);
    }
}

void checkbox(Task &task, std::vector<Task> &tasks, float animSpeed = 6.0f) {
    static std::unordered_map<std::string, float> checkboxAnims;
    float &animState = checkboxAnims[task.id];

    // Animate checkbox state
    float targetState = task.completed ? 1.0f : 0.0f;
    animState += (targetState - animState) * ImGui::GetIO().DeltaTime * animSpeed;

    ImDrawList *drawList = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    float size = 18.0f;
    float radius = 4.0f;

    // Background circle with smooth color transition
    ImVec4 bgColor = ImVec4(0.2f + animState * (task.color.x - 0.2f), 0.2f + animState * (task.color.y - 0.2f),
                            0.2f + animState * (task.color.z - 0.2f), 0.8f + animState * 0.2f);

    // Border animation
    float borderWidth = 1.5f + animState * 0.5f;
    ImU32 borderColor = ImGui::ColorConvertFloat4ToU32(ImVec4(task.color.x, task.color.y, task.color.z, 0.8f));
    ImU32 fillColor = ImGui::ColorConvertFloat4ToU32(bgColor);

    drawList->AddRectFilled(pos, ImVec2(pos.x + size, pos.y + size), fillColor, radius);
    drawList->AddRect(pos, ImVec2(pos.x + size, pos.y + size), borderColor, radius, 0, borderWidth);

    // Animated checkmark
    if (animState > 0.1f) {
        float checkAlpha = std::min(1.0f, (animState - 0.1f) * 1.5f);
        ImU32 checkColor = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, checkAlpha));

        ImVec2 center = ImVec2(pos.x + size * 0.5f, pos.y + size * 0.5f);
        ImVec2 checkStart = ImVec2(center.x - 4.0f, center.y);
        ImVec2 checkMid = ImVec2(center.x - 1.0f, center.y + 3.0f);
        ImVec2 checkEnd = ImVec2(center.x + 4.0f, center.y - 3.0f);

        drawList->AddLine(checkStart, checkMid, checkColor, 2.0f);
        drawList->AddLine(checkMid, checkEnd, checkColor, 2.0f);
    }

    // Invisible button for interaction
    ImGui::SetCursorScreenPos(pos);
    if (ImGui::InvisibleButton(("checkbox_" + task.id).c_str(), ImVec2(size, size))) {
        task.completed = !task.completed;
        update_task(tasks, task.id, task);
    }

    ImGui::SetCursorScreenPos(ImVec2(pos.x + size + 8.0f, pos.y));
}

void render_task_list(std::vector<Task> &tasks, float cardWidth, float cardHeight) {
    float padding = 16.0f;
    float regionWidth = ImGui::GetContentRegionAvail().x;
    int cardsPerRow = std::max(1, (int) ((regionWidth + padding) / (cardWidth + padding)));

    static std::unordered_map<std::string, float> cardHoverStates;
    static std::unordered_map<std::string, float> cardScaleStates;

    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 8.0f);
    ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, isDarkMode() ? WHITE : BLACK);

    ImGui::BeginChild("TaskListRegion", ImGui::GetContentRegionAvail(), false,
                      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                          ImGuiWindowFlags_AlwaysUseWindowPadding);

    for (size_t i = 0; i < tasks.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));
        Task &task = tasks[i];

        // Animation states
        float &hoverState = cardHoverStates[task.id];
        float &scaleState = cardScaleStates[task.id];

        int row = i / cardsPerRow;
        int col = i % cardsPerRow;

        if (col > 0) {
            ImGui::SameLine();
            ImGui::SetCursorPosX(col * (cardWidth + padding));
        }

        if (row > 0 && col == 0) {
            ImGui::Dummy(ImVec2(0.0f, padding));
        }

        ImVec2 cardPos = ImGui::GetCursorScreenPos();

        // Check if mouse is hovering over card area
        bool isCardHovered = ImGui::IsMouseHoveringRect(cardPos, ImVec2(cardPos.x + cardWidth, cardPos.y + cardHeight));

        // Animate hover state
        hoverState += (isCardHovered ? 1.0f : -1.0f) * ImGui::GetIO().DeltaTime * 8.0f;
        hoverState = std::max(0.0f, std::min(1.0f, hoverState));

        // Animate scale
        float targetScale = task.completed ? 0.98f : (1.0f + hoverState * 0.02f);
        scaleState += (targetScale - scaleState) * ImGui::GetIO().DeltaTime * 10.0f;

        // Modern card styling
        ImDrawList *drawList = ImGui::GetWindowDrawList();

        // Shadow effect
        float shadowOffset = 2.0f + hoverState * 8.0f;
        float shadowAlpha = 0.1f + hoverState * 0.15f;
        ImU32 shadowColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, shadowAlpha));

        drawList->AddRectFilled(ImVec2(cardPos.x + shadowOffset, cardPos.y + shadowOffset),
                                ImVec2(cardPos.x + cardWidth + shadowOffset, cardPos.y + cardHeight + shadowOffset),
                                shadowColor, 12.0f);

        // Card background with glassmorphism effect
        float bgAlpha = task.completed ? 0.08f : (0.15f + hoverState * 0.1f);
        ImVec4 cardBg = ImVec4(task.color.x, task.color.y, task.color.z, bgAlpha);

        drawList->AddRectFilled(cardPos, ImVec2(cardPos.x + cardWidth, cardPos.y + cardHeight),
                                ImGui::ColorConvertFloat4ToU32(cardBg), 12.0f);

        // Animated border
        float borderWidth = 1.0f + hoverState * 1.0f;
        float borderAlpha = task.completed ? 0.3f : (0.25f + hoverState * 0.4f);
        ImU32 borderColor =
            ImGui::ColorConvertFloat4ToU32(ImVec4(task.color.x, task.color.y, task.color.z, borderAlpha));

        drawList->AddRect(cardPos, ImVec2(cardPos.x + cardWidth, cardPos.y + cardHeight), borderColor, 12.0f, 0,
                          borderWidth);

        // Gradient overlay
        if (!task.completed) {
            ImU32 gradientTop = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 0.05f));
            ImU32 gradientBottom = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
            drawList->AddRectFilledMultiColor(cardPos, ImVec2(cardPos.x + cardWidth, cardPos.y + cardHeight * 0.5f),
                                              gradientTop, gradientTop, gradientBottom, gradientBottom);
        }

        // Card content
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18, 16));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));

        // Card Padding X
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 18);

        ImGui::BeginChild("TaskCard", ImVec2(cardWidth, cardHeight), false,
                          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

        // Dummy padding for Y
        ImGui::Dummy(ImVec2(0.0f, padding));

        // Title with completion styling
        float titleAlpha = task.completed ? 0.6f : 1.0f;
        ImGui::PushStyleColor(ImGuiCol_Text, isDarkMode() ? ImVec4(1.0f, 1.0f, 1.0f, titleAlpha)
                                                          : ImVec4(0.0f, 0.0f, 0.0f, titleAlpha));
        // Strikethrough effect for completed tasks
        if (task.completed) {
            ImVec2 titlePos = ImGui::GetCursorScreenPos();
            ImGui::Text("%s", task.title.c_str());
            ImVec2 titleSize = ImGui::CalcTextSize(task.title.c_str());
            drawList->AddLine(ImVec2(titlePos.x, titlePos.y + titleSize.y * 0.5f),
                              ImVec2(titlePos.x + titleSize.x, titlePos.y + titleSize.y * 0.5f),
                              ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 0.7f)), 1.5f);
        } else {
            ImGui::Text("%s", task.title.c_str());
        }
        ImGui::PopStyleColor();

        ImGui::Spacing();

        // Content with fade effect for completed tasks
        float contentAlpha = task.completed ? 0.5f : 0.8f;
        ImGui::PushStyleColor(ImGuiCol_Text, isDarkMode() ? ImVec4(0.9f, 0.9f, 0.9f, contentAlpha)
                                                          : ImVec4(0.1f, 0.1f, 0.1f, contentAlpha));
        ImGui::TextWrapped("%s", task.content.c_str());
        ImGui::PopStyleColor();

        ImGui::Dummy(ImVec2(0.0f, 12.0f));

        ImGui::BeginGroup();
        checkbox(task, tasks);
        ImGui::SameLine();

        float doneAlpha = task.completed ? 0.8f : 0.6f;
        ImGui::PushStyleColor(ImGuiCol_Text,
                              isDarkMode() ? ImVec4(1.0f, 1.0f, 1.0f, doneAlpha) : ImVec4(0.0f, 0.0f, 0.0f, doneAlpha));
        ImGui::Text("Done");
        ImGui::PopStyleColor();
        ImGui::EndGroup();

        ImGui::SameLine();
        ImGui::SetCursorPosX(cardWidth - 50);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY());
        delete_button(tasks, task.id);

        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::PopID();
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}
