#include "main/editor/Editor.h"
#include "main/editor/PerformancePanel.h"
#include "main/editor/ScenePanel.h"
#include "external/imgui/rlImGui.h"
#include "main/physics/Config.h"

namespace Editor {

Editor::Editor(World& world, EditorCamera& camera, InputHandler& input) {
    panels.push_back(std::make_unique<PerformancePanel>(camera, input));
    panels.push_back(std::make_unique<ScenePanel>(Config::screenWidth, Config::screenHeight));
}

Editor::~Editor() {
}

void Editor::Update(World& world) {
    rlImGuiBegin();

    for (auto& panel : panels) {
        panel->OnImGui(world);
    }

    rlImGuiEnd();
}

} // namespace Editor
