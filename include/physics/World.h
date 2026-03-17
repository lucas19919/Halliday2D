#pragma once
#include <vector>
#include "RigidBody.h"

class World
{
    public:
        Vec2 gravity;

        World();
        void AddBody(RigidBody* body);
        void Step(float dt);
    private:
        std::vector<RigidBody*> bodies;
        
};