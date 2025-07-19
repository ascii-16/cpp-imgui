#include <imgui.h>

/**
 * @brief Renders a toggle button for switching between dark and light UI modes.
 *
 * This function displays a button that allows the user to switch between dark and light color themes for the application UI.
 * The current mode is tracked using a static boolean. When toggled, the ImGui style is updated accordingly.
 */
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