#include "raylib.h"
#include "physics/world.h"
#include "physics/RigidBody.h"
#include "math/Vec2.h"
#include <vector>

int main() {
    const int ScreenWidth = 1280;
    const int ScreenHeight = 960;

    InitWindow(ScreenWidth, ScreenHeight, "Engine 1.0");
    SetTargetFPS(60);

    World world;
    RigidBody body(10.0f, Vec2(ScreenWidth/2, 0), Vec2(), Vec2(), Vec2());
    world.AddBody(&body);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        world.Step(dt);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircle(body.postion.x, body.postion.y, 100, DARKBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}