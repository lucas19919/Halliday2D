#include "math/Vec2.h"

class GameObject;

class RigidBody 
{
    public: 
        RigidBody(float m, Vec2 pos, Vec2 v, Vec2 a, Vec2 F, float r, float e);
        ~RigidBody();

        GameObject* parent;

        Vec2 velocity;
        Vec2 acceleration;

        void SetMass(float m);
        float GetMass() const { return mass; }
        float GetInvMass() const { return invMass; }

        float GetRadius() const { return radius; }
        float GetRes() const { return restitution; }
        void ApplyForce(Vec2 force);
        void ClearForces();
        Vec2 GetForce() const { return forceSum; }
    private:
        float mass;
        float invMass;
        float radius;
        float restitution;
        Vec2 forceSum;
};