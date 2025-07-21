#include <imgui.h>

bool isDarkMode() {
    ImVec4 bgColor = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
    bool isDark = bgColor.x < 0.5f && bgColor.y < 0.5f && bgColor.z < 0.5f;
    return isDark;
}