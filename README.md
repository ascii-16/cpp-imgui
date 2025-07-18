# cpp-gui

A modern C++ GUI application using [Dear ImGui](https://github.com/ocornut/imgui) and CMake. This project demonstrates a simple, extensible graphical user interface with support for tasks, image handling, and persistent storage.

## Project Structure
- `main.cpp` — Application entry point
- `lib/` — Core logic (image handling, storage, UUID)
- `ui/` — UI components (task list, add task button, etc.)
- `external/` — Third-party single-header libraries (e.g., nlohmann/json, stb_image)
- `vendor/imgui/` — Dear ImGui source and backends
- `assets/` — Icons and other static assets

## Build Instructions

1. **Clone the repository**:
   ```sh
   git clone <repo-url>
   cd cpp-gui
   ```

2. **Create a build directory:**
   ```sh
   mkdir build
   cd build
   ```

3. **Generate build files with CMake:**
   ```sh
   cmake ..
   ```

4. **Build the project:**
   ```sh
   make
   ```

5. **Run the application:**
   ```sh
   ./ImGuiApp
   ```

## Requirements
- C++17 or newer compiler
- CMake 3.10+
- [Dear ImGui](https://github.com/ocornut/imgui) (included as a subdirectory)
- Platform-specific dependencies (e.g., OpenGL, SDL2, GLFW, etc. — see CMakeLists.txt)

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE.txt) for details.

---
