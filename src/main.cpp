#include "raylib.h"
#include "main/World.h"
#include "main/GameObject.h"
#include "main/scenes/LoadScene.h"
#include "main/utility/Draw.h"
#include "main/utility/InputHandler.h"
#include "main/physics/Config.h"
#include <string>

int main() {
    const int screenWidth = Config().screenWidth;
    const int screenHeight = Config().screenHeight;

    World world;
    InputHandler input;

    //all levels under ../assets/( ... ).json
    const std::string& filepath = "../assets/shapes.json";
    LoadScene::Load(filepath, world, screenWidth, screenHeight);
    
    InitWindow(screenWidth, screenHeight, "Engine 1.0");
    SetTargetFPS(Config().targetFPS);    

    //draw fps?
    bool FPS = true;

    const float dt = 1.0f / 60.0f;
    while (!WindowShouldClose()) {
        input.Update(world, filepath, screenWidth, screenHeight);
        world.Step(dt);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (const auto& objPtr : world.GetGameObjects())
            {
                Render(objPtr.get());
            }
            if (FPS)
                DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}