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
        rb->acceleration = rb->GetForce() * iM;
        rb->velocity += rb->acceleration * dt;
        rb->postion += rb->velocity * dt;

        rb->ClearForces();
    }
}

void World::CheckCollisons(int screenWidth, int screenHeight)
{
    for (int i = 0; i < bodies.size(); i++)
    {
        RigidBody *rb = bodies[i];
    
        float radius = rb->GetRadius();
        if (rb->postion.x + radius > screenWidth)
        {
            rb->postion.x = screenWidth - radius;
            rb->velocity.x *= -1; 
        }
        
        if (rb->postion.x - radius < 0)
        {
            rb->postion.x = radius;
            rb->velocity.x *= -1; 
        }

        if (rb->postion.y + radius > screenHeight)
        {
            rb->postion.y = screenHeight - radius;
            rb->velocity.y *= -1; 
        }
        
        if (rb->postion.y - radius < 0)
        {
            rb->postion.y = radius;
            rb->velocity.y *= -1; 
        }

        for (int j = i + 1; j < bodies.size(); j++)
        {
            RigidBody *rbB = bodies[j];

            Vec2 dir = rbB->postion - rb->postion;
            Vec2 dirN = dir.Norm();
            if (dir.MagSq() < (rbB->GetRadius() + rb->GetRadius()) * (rbB->GetRadius() + rb->GetRadius()))
            {
                Vec2 relativeV = rbB->velocity - rb->velocity;
                float dot = relativeV.Dot(dirN);
                if (dot > 0) continue;
                
                float bounce = (rb->GetRes() + rbB->GetRes()) / 2.0f; 
                float impulse = -1 * (1 + bounce) * dot / (rb->GetInvMass() + rbB->GetInvMass());
                Vec2 impulseVec = dirN * impulse;

                rb->velocity += impulseVec * rb->GetInvMass() * -1;
                rbB->velocity += impulseVec * rbB->GetInvMass();
            }
        }
    }
}