#include "raylib.h"
#include "main/World.h"
#include "main/GameObject.h"
#include "math/Vec2.h"
#include "main/components/collidertypes/BoxCollider.h"
#include "main/components/collidertypes/CircleCollider.h"
#include <vector>
#include "main/utility/Draw.h"
#include "main/utility/Instantiate.h"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 960;

    World world;

    bool wallCollisions = true;
    if (wallCollisions)
    {
        GameObject* floor = Instantiate()
            .WithTransform(Vec2(screenWidth / 2.0f, screenHeight + 25.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(screenWidth, 50.0f))
            .Create(world);

        GameObject* ceiling = Instantiate()
            .WithTransform(Vec2(screenWidth / 2.0f, -25.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(screenWidth, 50.0f))
            .Create(world);

        GameObject* leftWall = Instantiate()
            .WithTransform(Vec2(-25.0f, screenHeight / 2.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(50.0f, screenHeight))
            .Create(world);

        GameObject* rightWall = Instantiate()
            .WithTransform(Vec2(screenWidth + 25.0f, screenHeight / 2.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(50.0f, screenHeight))
            .Create(world);
    }

    Properties properties = { 1.0f, 0.5f, 100.0f };//, 1.0f };
    LinearState linearState = { Vec2(100.0f, 0.0f), Vec2(), Vec2() };
    AngularState angularState = { 1.0f, 0.0f, 0.0f };
    
    GameObject* obj = Instantiate()
        .WithTransform(Vec2(screenWidth / 2, 50.0f), 0.0f)
        .WithCollider(ColliderType::BOX, Vec2(30.0f, 50.0f))
        .WithRenderer({ RenderShape::R_BOX, BLUE, { Vec2(30.0f, 50.0f) } })
        .WithRigidBody(properties, linearState, angularState)
        .Create(world);

    InitWindow(screenWidth, screenHeight, "Engine 1.0");
    SetTargetFPS(60);    

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        world.Step(dt);
        world.CheckCollisons(screenWidth, screenHeight);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            Render(obj);
        EndDrawing();

        DrawFPS(10, 10);
    }

    CloseWindow();
    return 0;
}