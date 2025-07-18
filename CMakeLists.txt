cmake_minimum_required(VERSION 3.10)
project(ImGuiApp)

set(CMAKE_CXX_STANDARD 17)



# Find GLFW
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/glfw")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

find_package(OpenGL REQUIRED)

# ImGui sources
file(GLOB IMGUI_SOURCES
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

include_directories(
    vendor/imgui
    vendor/imgui/backends
    ${GLFW_INCLUDE_DIRS}
)

add_executable(ImGuiApp main.cpp ${IMGUI_SOURCES})

target_link_libraries(ImGuiApp
    ${GLFW_LIBRARIES}
    OpenGL::GL
)
