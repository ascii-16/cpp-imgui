#include <imgui.h>

void mode_toggle_button() {
    static bool isDarkMode = true;
    static ImVec4 color = ImVec4(51.0f / 255.0f, 153.0f / 255.0f, 204.0f / 255.0f, 1.0f);

    float windowWidth = ImGui::GetContentRegionAvail().x;

    ImGui::SetCursorPosX(windowWidth - 100.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
    ImGui::PushStyleColor(ImGuiCol_Button, color);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x * 1.1f, color.y * 1.1f, color.z * 1.1f, color.w));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x * 0.9f, color.y * 0.9f, color.z * 0.9f, color.w));
    
    if (ImGui::Button(isDarkMode ? "Dark Mode" : "Light Mode")) {
        isDarkMode = !isDarkMode;

        if (isDarkMode)
            ImGui::StyleColorsDark();
        else
            ImGui::StyleColorsLight();
    }

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
    ImGui::Spacing();
}