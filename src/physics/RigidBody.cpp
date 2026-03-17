#include "physics/RigidBody.h"
#include "math/Vec2.h"

RigidBody::RigidBody(float setMass, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force)
{
    mass = setMass;
    invMass = 1 / setMass;
    postion = position;
    velocity = velocity;
    acceleration = acceleration;
    forceSum = force;
}

void RigidBody::SetMass(float setMass)
{
    mass = setMass;
    invMass = 1 / setMass;
}

void RigidBody::ApplyForce(Vec2 force)
{
    forceSum += force;
}

void RigidBody::ClearForces() 
{
    forceSum = Vec2(0.0f, 0.0f);
}