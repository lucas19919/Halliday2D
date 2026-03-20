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

        floor->transform.position = Vec2(screenWidth / 2.0f, screenHeight);
        ceiling->transform.position = Vec2(screenWidth / 2.0f, 0.0f);
        leftWall->transform.position = Vec2(0.0f, screenHeight / 2.0f);
        rightWall->transform.position = Vec2(screenWidth, screenHeight / 2.0f);

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

    GameObject* obj = new GameObject();
    obj->transform.position = Vec2(screenWidth / 2, 50.0f);
    Collider* col = new CircleCollider(15.0f);
    obj->SetCollider(col);
    Renderer* rend = new Renderer(BLUE);
    obj->SetRenderer(rend);
    RigidBody* rb = new RigidBody(1.0f, 0.5f, Vec2(100.0f, 0.0f), Vec2(), Vec2());
    obj->SetRigidBody(rb);

    GameObject* obj2 = new GameObject();
    obj2->transform.position = Vec2(screenWidth / 2 + 100.0f, 50.0f);
    Collider* col2 = new BoxCollider(Vec2(50.0f, 50.0f));
    obj2->SetCollider(col2);
    Renderer* rend2 = new Renderer(RED);
    obj2->SetRenderer(rend2);
    RigidBody* rb2 = new RigidBody(1.0f, 0.5f, Vec2(-100.0f, 0.0f), Vec2(), Vec2());
    obj2->SetRigidBody(rb2);

    GameObject* obj3 = new GameObject();
    obj3->transform.position = Vec2(screenWidth / 2 + 200.0f, 50.0f);
    Collider* col3 = new BoxCollider(Vec2(50.0f, 50.0f));
    obj3->SetCollider(col3);
    Renderer* rend3 = new Renderer(GREEN);
    obj3->SetRenderer(rend3);
    RigidBody* rb3 = new RigidBody(1.0f, 0.5f, Vec2(0.0f, 0.0f), Vec2(), Vec2());
    obj3->SetRigidBody(rb3);

    world.AddGameObject(obj);
    world.AddGameObject(obj2);
    world.AddGameObject(obj3);

    InitWindow(screenWidth, screenHeight, "Engine 1.0");
    SetTargetFPS(60);    

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        world.Step(dt);
        world.CheckCollisons(screenWidth, screenHeight);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            CircleCollider* c = static_cast<CircleCollider*>(obj->GetCollider());
            DrawCircle(obj->transform.position.x, obj->transform.position.y, c->radius, obj->GetRenderer()->color);

            BoxCollider* b = static_cast<BoxCollider*>(obj2->GetCollider());
            DrawRectangle(obj2->transform.position.x - b->size.x / 2, obj2->transform.position.y - b->size.y / 2, b->size.x, b->size.y, obj2->GetRenderer()->color);

            BoxCollider* b2 = static_cast<BoxCollider*>(obj3->GetCollider());
            DrawRectangle(obj3->transform.position.x - b2->size.x / 2, obj3->transform.position.y - b2->size.y / 2, b2->size.x, b2->size.y, obj3->GetRenderer()->color);
        EndDrawing();

        DrawFPS(10, 10);
    }

    CloseWindow();
    return 0;
}