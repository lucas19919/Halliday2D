#include "main/World.h"
#include "main/GameObject.h"
#include "math/Vec2.h"

World::World()
{
    gravity = Vec2(0.0f, 981.0f);
    airDensity = 0.001f;
}

World::~World()
{
    for (GameObject* obj : GetGameObjects()) {
        delete obj;
    }
    GetGameObjects().clear();
}

void World::Step(float dt)
{
    for (GameObject *obj : GetGameObjects())
    {
        RigidBody *rb = obj->GetRigidBody();
        Collider *c = obj->GetCollider();
        if (rb == nullptr) continue;

        float iM = rb->GetInvMass();
        float M = rb->GetMass();

        rb->ApplyForce(gravity * M);

        /*float speedSq = rb->velocity.MagSq();
        if (speedSq > 0.0001f)
        {
            float drag = airDensity * speedSq * rb->GetRadius();
            rb->ApplyForce(rb->velocity.Norm() * -1.0f * drag);
        }*/
       
        rb->acceleration = rb->GetForce() * iM;
        rb->velocity += rb->acceleration * dt;

        obj->transform.position += rb->velocity * dt;

        rb->ClearForces();
    }
}

void World::CheckCollisons(int screenWidth, int screenHeight)
{
    for (int i = 0; i < GetGameObjects().size(); i++)
    {
        GameObject* obj = GetGameObjects()[i];
        RigidBody* rb = obj->GetRigidBody();
        if (rb == nullptr) continue;

        Collider* c = obj->GetCollider();
        if (c == nullptr) continue;

        
    }
}