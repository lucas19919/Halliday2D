#include "main/editor/Editor.h"
#include "main/editor/PerformancePanel.h"
#include "main/editor/ScenePanel.h"
#include "main/editor/ViewportPanel.h"
#include "external/imgui/imgui.h"
#include "external/imgui/rlImGui.h"
#include "main/physics/Config.h"

namespace Editor {

Editor::Editor(World& world, EditorCamera& camera, InputHandler& input) {
    panels.push_back(std::make_unique<ViewportPanel>(camera));
    panels.push_back(std::make_unique<PerformancePanel>(camera, input));
    panels.push_back(std::make_unique<ScenePanel>(Config::screenWidth, Config::screenHeight));
}

Editor::~Editor() {
}

void Editor::Update(World& world) {
    rlImGuiBegin();

    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) { /* Handle exit */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            for (auto& panel : panels)
            {
                ImGui::MenuItem(panel->GetName(), nullptr, &panel->isOpen);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    for (auto& panel : panels) {
        panel->OnImGui(world);
    }

    ImGui::End(); // End DockSpace window

    rlImGuiEnd();
}

} // namespace Editor
