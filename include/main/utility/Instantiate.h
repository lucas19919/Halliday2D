#pragma once
#include "main/GameObject.h"
#include "main/World.h"

class Instantiate
{
    public:
        Instantiate();

        Instantiate& WithRigidBody(Properties properties, LinearState linearState, AngularState angularState);
        Instantiate& WithRenderer(Shape shape);
        Instantiate& WithCollider(ColliderType type, Vec2 size = Vec2(), float radius = 0.0f);
        Instantiate& WithTransform(Vec2 position, float rotation);

        GameObject* Create(World& world);
    private:
        GameObject* obj;
};