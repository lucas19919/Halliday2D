#include "raylib.h"
#include "external/imgui/imgui.h"
#include "external/imgui/rlImGui.h"
#include "main/World.h"
#include "main/GameObject.h"
#include "main/scenes/LoadScene.h"
#include "main/utility/Draw.h"
#include "main/utility/InputHandler.h"
#include "main/physics/Config.h"
#include "main/utility/EditorCamera.h"
#include <string>

int main() {
    const int screenWidth = Config::screenWidth;
    const int screenHeight = Config::screenHeight;

    InitWindow(screenWidth, screenHeight, "Halliday2D");
    SetTargetFPS(Config::targetFPS);    

    rlImGuiSetup(true);

    World world;
    InputHandler input;
    EditorCamera camera((float)screenWidth, (float)screenHeight);

    std::string selectedFile = "../assets/examples/PrattTruss.json";
    char filePathBuffer[256] = "../assets/examples/";

    LoadScene::Load(selectedFile, world, screenWidth, screenHeight);

    //draw fps?
    bool FPS = Config::drawFPS;

    const float dt = 1.0f / 60.0f;
    while (!WindowShouldClose()) {
        input.Update(world, camera, selectedFile, screenWidth, screenHeight, dt);
        
        GizmoUpdate(camera);

        world.Step(dt);

        BeginDrawing();
            ClearBackground(GRAY);

            camera.Begin();
                Render(world, camera); 
            camera.End();
            
            GizmoRender(camera);

            rlImGuiBegin();
            ImGui::Begin("Physics Tools");
            
            ImGui::InputText("Level Path", filePathBuffer, 256);
            
            if (ImGui::Button("Load Level")) {
                selectedFile = filePathBuffer;
                world.isPaused = true;
                world.Clear();
                
                LoadScene::Load(selectedFile, world, screenWidth, screenHeight);  
            }

            if (!selectedFile.empty()) {
                ImGui::Text("Currently active file: %s", selectedFile.c_str());
            }

            ImGui::Separator();
            ImGui::Text("Viewport Info:");
            ImGui::Text("Zoom: %.2fx", camera.GetRaylibCamera().zoom);
            Vec2 mousePos = input.GetMouseWorldPos();
            ImGui::Text("Mouse World (m): %.2f, %.2f", mousePos.x, mousePos.y);

            ImGui::Separator();
            ImGui::Text("Timing:");
            ImGui::Text("Integrate Velocity Time: %.2f ms", world.integrateVelocityTime);
            ImGui::Text("Integrate Position Time: %.2f ms", world.integratePositionTime);
            ImGui::Text("Broadphase Time: %.2f ms", world.broadphaseTime);
            ImGui::Text("Solver Time: %.2f ms", world.solverTime);

            ImGui::End();

            rlImGuiEnd();
            
            if (FPS) {
                DrawFPS(10, 10);
            }
        
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}