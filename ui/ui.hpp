#pragma once

#include <vector>
#include "task.hpp"

/**
 * @brief Renders a toggle button for switching between dark and light UI modes.
 *
 * This function displays a button that allows the user to switch between dark and light color themes for the
 * application UI. The current mode is tracked using a static boolean. When toggled, the ImGui style is updated
 * accordingly.
 */
void render_task_list(std::vector<Task> &tasks, float cardWidth = 220.0f, float cardHeight = 120.0f);

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
void add_task_form(std::vector<Task> &tasks, char *titleBuffer, char *contentBuffer, ImVec4 &color);

/**
 * @brief Renders a toggle button for switching between dark and light UI modes.
 *
 * This function displays a button that allows the user to switch between dark and light color themes for the
 * application UI. The current mode is tracked using a static boolean. When toggled, the ImGui style is updated
 * accordingly.
 */
void mode_toggle_button();

/**
 * @brief Renders a custom button with an icon and text.
 *
 * This function creates an invisible button and manually draws a rectangular background,
 * an image (icon), and a label text. The button supports custom icon size, spacing between
 * the icon and text, padding, and background color.
 *
 * @param iconTex      The OpenGL texture ID (as `const char*`) for the icon image. Should point to a loaded texture.
 * @param text         The text label to be displayed next to the icon.
 * @param iconSize     The size of the icon to be displayed. Defaults to 18x18 pixels.
 * @param spacing      The space between the icon and the text. Defaults to 6.0f.
 * @param padding      The padding inside the button around the content. Defaults to (20, 12).
 * @param buttonColor  The background color of the button in IM_COL32 format. Defaults to a blue color.
 * @param hoverColor   The background color of the button when hovered in IM_COL32 format.
 *
 * @return true if the button is clicked (pressed), false otherwise.
 */
bool button_with_icon(const char *iconTex, const char *text, ImVec2 iconSize = ImVec2((float) 18, (float) 18),
                      float spacing = 6.0f, ImVec2 padding = ImVec2((float) 20, (float) 12),
                      ImU32 buttonColor = IM_COL32(51, 153, 204, 255), ImU32 hoverColor = IM_COL32(56, 168, 224, 255));