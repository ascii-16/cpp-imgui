#include <imgui.h>

void mode_toggle_button() {
    static bool isDarkMode = true;

    if (ImGui::Button(isDarkMode ? "Dark Mode" : "Light Mode")) {
        isDarkMode = !isDarkMode;

        if (isDarkMode)
            ImGui::StyleColorsDark();
        else
            ImGui::StyleColorsLight();
    }
}