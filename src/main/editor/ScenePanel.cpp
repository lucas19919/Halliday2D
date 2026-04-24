#include "main/editor/ScenePanel.h"
#include "external/imgui/imgui.h"
#include "main/scenes/LoadScene.h"
#include "main/editor/EditorState.h"
#include <cstring>

namespace Editor {

ScenePanel::ScenePanel(int screenWidth, int screenHeight) 
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    std::strncpy(filePathBuffer, "../assets/examples/", sizeof(filePathBuffer));
}

void ScenePanel::OnImGui(World& world) {
    if (!isOpen) return;

    ImGui::Begin(GetName(), &isOpen);
    
    ImGui::InputText("Level Path", filePathBuffer, 256);
    
    if (ImGui::Button("Load Level")) {
        EditorState::Get().SetActiveScenePath(filePathBuffer);
        world.isPaused = true;
        world.Clear();
        LoadScene::Load(EditorState::Get().GetActiveScenePath(), world, screenWidth, screenHeight);  
    }

    if (!EditorState::Get().GetActiveScenePath().empty()) {
        ImGui::Text("Currently active file: %s", EditorState::Get().GetActiveScenePath().c_str());
    }

    ImGui::End();
}

} // namespace Editor
