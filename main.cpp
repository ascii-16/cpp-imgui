#include <vector>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "Task.hpp"

int main()
{
    std::vector<Task> tasks;

    static char titleBuffer[128] = "";
    static char contentBuffer[256] = "";
    static ImVec4 color = ImVec4(0.5f, 0.8f, 0.5f, 1.0f);
    static ImVec2 position = ImVec2(50, 50);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(1400, 900, "Sample GUI app", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("Task Manager", nullptr,
                     ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoSavedSettings);

        ImGui::InputText("Title", titleBuffer, IM_ARRAYSIZE(titleBuffer));
        ImGui::InputTextMultiline("Content", contentBuffer, IM_ARRAYSIZE(contentBuffer));
        ImGui::ColorEdit4("Color", (float *)&color);

        if (ImGui::Button("Add Task"))
        {
            static float posX = 0.0f;
            static float posY = 0.0f;
            float padding = 10.0f;
            float regionWidth = ImGui::GetContentRegionAvail().x;
            ImVec2 cardSize = ImVec2(200, 100);

            if (posX + cardSize.x > regionWidth)
            {
                posX = 0.0f;
                posY += cardSize.y + padding;
            }

            tasks.push_back(Task{
                .title = titleBuffer,
                .content = contentBuffer,
                .position = ImVec2(posX, posY),
                .color = color,
                .completed = false});

            posX += cardSize.x + padding;

            titleBuffer[0] = '\0';
            contentBuffer[0] = '\0';
        }

        ImGui::BeginChild("TaskListRegion",
                          ImGui::GetContentRegionAvail(),
                          false,
                          ImGuiWindowFlags_NoResize |
                              ImGuiWindowFlags_NoMove |
                              ImGuiWindowFlags_NoSavedSettings |
                              ImGuiWindowFlags_AlwaysUseWindowPadding);

        for (size_t i = 0; i < tasks.size(); ++i)
        {
            ImGui::PushID(i);
            Task &task = tasks[i];

            ImGui::SetCursorPos(task.position);

            ImGui::PushStyleColor(ImGuiCol_ChildBg, task.color);

            ImGui::BeginChild("TaskCard", ImVec2(200, 100), true, ImGuiWindowFlags_NoMove);

            ImGui::Text("%s", task.title.c_str());
            ImGui::Separator();
            ImGui::TextWrapped("%s", task.content.c_str());
            ImGui::Checkbox("Done", &task.completed);

            ImGui::EndChild();
            ImGui::PopStyleColor();

            ImGui::PopID();
        }
        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();

        int w, h;

        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}