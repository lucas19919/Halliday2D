#pragma once
#include "math/Vec2.h"

class RigidBody 
{
    public: 
        Vec2 postion;
        Vec2 velocity;
        Vec2 acceleration;

        RigidBody(float setMass, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force);

        void SetMass(float setMass);
        float GetMass() const { return mass; }
        float GetInvMass() const { return invMass; }

        void ApplyForce(Vec2 force);
        void ClearForces();
        Vec2 GetForce() const { return forceSum; }
    private:
        float mass;
        float invMass;
        Vec2 forceSum;
};