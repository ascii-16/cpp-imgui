#include <imgui.h>
#include <algorithm>
#include "image.hpp"

bool button_with_icon(const char *iconPath, const char *text, ImVec2 iconSize, float spacing, ImVec2 padding,
                      ImU32 buttonColor, ImU32 hoverColor) {

    GLuint iconTex = LoadPNGTexture(iconPath);
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 buttonSize =
        ImVec2(iconSize.x + spacing + textSize.x + padding.x * 2, std::max(iconSize.y, textSize.y) + padding.y * 2);

    bool pressed = ImGui::InvisibleButton("##btn", buttonSize);

    ImVec2 cursor = ImGui::GetItemRectMin();
    ImVec2 iconPos = ImVec2(cursor.x + padding.x, cursor.y + padding.y);
    ImVec2 iconEnd = ImVec2(iconPos.x + iconSize.x, iconPos.y + iconSize.y);
    ImVec2 textPos = ImVec2(iconEnd.x + spacing, cursor.y + padding.y);
    ImU32 bgColor = (ImGui::IsItemHovered() || ImGui::IsItemActive()) ? hoverColor : buttonColor;

    // Draw button with bg color
    ImGui::GetWindowDrawList()->AddRectFilled(cursor, ImVec2(cursor.x + buttonSize.x, cursor.y + buttonSize.y), bgColor,
                                              4.0f);

    // Draw icon
    ImGui::GetWindowDrawList()->AddImage((ImTextureID) (intptr_t) iconTex, iconPos, iconEnd);

    // Draw text
    ImGui::GetWindowDrawList()->AddText(textPos, ImGui::GetColorU32(ImGuiCol_Text), text);

    return pressed;
}