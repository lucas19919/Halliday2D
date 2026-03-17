#include "raylib.h"
#include "physics/world.h"
#include "physics/RigidBody.h"
#include "math/Vec2.h"
#include <vector>

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "Engine 1.0");
    SetTargetFPS(60);

    World world;
    RigidBody body(10.0f, Vec2(screenWidth/2, 0), Vec2(100.0f, 0.0f), Vec2(), Vec2(), 50.0f, 1.0f);
    RigidBody body2(10.0f, Vec2(), Vec2(), Vec2(), Vec2(), 50.0f, 1.0f);

    world.AddBody(&body);
    world.AddBody(&body2);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        world.Step(dt);
        world.CheckCollisons(screenWidth, screenHeight);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (RigidBody* rb : world.bodies)
            {
                DrawCircle(rb->postion.x, rb->postion.y, rb->GetRadius(), DARKBLUE);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}