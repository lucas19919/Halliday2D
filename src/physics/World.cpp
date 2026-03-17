#include "physics/World.h"
#include "physics/RigidBody.h"
#include "math/Vec2.h"

World::World()
{
    gravity = Vec2(0.0f, 9.81f);
}

void World::AddBody(RigidBody* body)
{
    bodies.push_back(body);
}

void World::Step(float dt)
{
    for (RigidBody *rb : bodies)
    {
        float iM = rb->GetInvMass();
        float M = rb->GetMass();

        rb->ApplyForce(gravity * M);
        rb->acceleration += rb->GetForce() * iM;
        rb->velocity += rb->acceleration * dt;
        rb->postion += rb->velocity * dt;

        rb->ClearForces();
    }
}