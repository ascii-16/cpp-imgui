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
    // TODO: get rid of IM_ARRAYSIZE and use template/ pass buffer size explicitily instead
    ImGui::InputText("Title", titleBuffer, IM_ARRAYSIZE(titleBuffer));
    ImGui::InputTextMultiline("Content", contentBuffer, IM_ARRAYSIZE(contentBuffer));
    ImGui::ColorEdit4("Color", (float *) &color);
    if (ImGui::Button("Add Task")) {
        tasks.insert(tasks.begin(), Task{.id = generate_uuid(),
                                         .title = titleBuffer,
                                         .content = contentBuffer,
                                         .color = color,
                                         .completed = false});

        titleBuffer[0] = '\0';
        contentBuffer[0] = '\0';

        save_tasks(tasks, "tasks.json");
    }
}