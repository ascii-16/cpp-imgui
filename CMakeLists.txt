cmake_minimum_required(VERSION 3.10)
project(ImGuiApp)

set(CMAKE_CXX_STANDARD 17)

# Find GLFW
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/glfw")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/ui)
include_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${GLFW_LIBRARY_DIRS})

find_package(OpenGL REQUIRED)

# ImGui sources
file(GLOB IMGUI_SOURCES
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# UI
file(GLOB UI_SOURCES "ui/*.cpp")
file(GLOB UI_HEADERS "ui/*.hpp")

# Lib
file(GLOB LIB_SOURCES "lib/*.cpp")
file(GLOB LIb_HEADERS "lib/*.hpp")

include_directories(
    vendor/imgui
    vendor/imgui/backends
    external
    ${GLFW_INCLUDE_DIRS}
)

add_executable(ImGuiApp main.cpp ${UI_SOURCES} ${UI_HEADERS} ${LIB_SOURCES} ${LIB_HEADERS} ${IMGUI_SOURCES})

target_include_directories(ImGuiApp PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(ImGuiApp
    ${GLFW_LIBRARIES}
    OpenGL::GL
)
