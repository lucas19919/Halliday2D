#include "raylib.h"
#include "main/World.h"
#include "main/GameObject.h"
#include "math/Vec2.h"
#include "main/components/collidertypes/BoxCollider.h"
#include "main/components/collidertypes/CircleCollider.h"
#include <vector>

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 960;

    World world;

    bool wallCollisions = true;
    if (wallCollisions)
    {
        GameObject* floor = new GameObject();
        GameObject* ceiling = new GameObject();
        GameObject* leftWall = new GameObject();
        GameObject* rightWall = new GameObject();

        floor->transform.position = Vec2(screenWidth / 2.0f, screenHeight + 25.0f);
        ceiling->transform.position = Vec2(screenWidth / 2.0f, -25.0f);
        leftWall->transform.position = Vec2(-25.0f, screenHeight / 2.0f);
        rightWall->transform.position = Vec2(screenWidth + 25.0f, screenHeight / 2.0f);

        BoxCollider* floorCollider = new BoxCollider(Vec2(screenWidth, 50.0f));
        BoxCollider* ceilingCollider = new BoxCollider(Vec2(screenWidth, 50.0f));
        BoxCollider* leftWallCollider = new BoxCollider(Vec2(50.0f, screenHeight));
        BoxCollider* rightWallCollider = new BoxCollider(Vec2(50.0f, screenHeight));

        floor->SetCollider(floorCollider);
        ceiling->SetCollider(ceilingCollider);
        leftWall->SetCollider(leftWallCollider);
        rightWall->SetCollider(rightWallCollider);

        world.AddGameObject(floor);
        world.AddGameObject(ceiling);
        world.AddGameObject(leftWall);
        world.AddGameObject(rightWall);
    }

    Properties properties = { 1.0f, 0.5f, 100.0f };
    LinearState linearState = { Vec2(100.0f, 0.0f), Vec2(), Vec2() };
    AngularState angularState = { 1.0f, 0.0f, 0.0f };

    GameObject* obj = new GameObject();
    obj->transform.position = Vec2(screenWidth / 2, 50.0f);
    Collider* col = new BoxCollider(Vec2(30.0f, 50.0f));
    obj->SetCollider(col);
    Renderer* rend = new Renderer(BLUE); //set collider pre renderer
    obj->SetRenderer(rend);
    RigidBody* rb = new RigidBody(properties, linearState, angularState);
    obj->SetRigidBody(rb);

    world.AddGameObject(obj);


    InitWindow(screenWidth, screenHeight, "Engine 1.0");
    SetTargetFPS(60);    

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        world.Step(dt);
        world.CheckCollisons(screenWidth, screenHeight);

BeginDrawing();
    ClearBackground(RAYWHITE);

    BoxCollider* b = static_cast<BoxCollider*>(obj->GetCollider());
    
    Rectangle rec = { 
        obj->transform.position.x, 
        obj->transform.position.y, 
        b->size.x, 
        b->size.y 
    };
    
    Vector2 origin = { b->size.x / 2.0f, b->size.y / 2.0f };
    float rotDegrees = obj->transform.rotation * RAD2DEG;
    
    DrawRectanglePro(rec, origin, rotDegrees, BLUE);

EndDrawing();

        DrawFPS(10, 10);
    }

    CloseWindow();
    return 0;
}