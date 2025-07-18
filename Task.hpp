#pragma once

#include <string>
#include "imgui.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Task {
    std::string id;
    std::string title;
    std::string content;
    ImVec2 position;
    ImVec4 color;
    bool completed;
};

inline void to_json(json &j, const Task &t) {
    j = json{{"title", t.title},
             {"content", t.content},
             {"position", {t.position.x, t.position.y}},
             {"color", {t.color.x, t.color.y, t.color.z, t.color.w}},
             {"completed", t.completed}};
}

inline void from_json(const json &j, Task &t) {
    t.title = j.at("title").get<std::string>();
    t.content = j.at("content").get<std::string>();
    auto pos = j.at("position");
    t.position = ImVec2(pos[0], pos[1]);
    auto col = j.at("color");
    t.color = ImVec4(col[0], col[1], col[2], col[3]);
    t.completed = j.at("completed").get<bool>();
}