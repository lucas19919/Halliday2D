#include "main/components/RigidBody.h"
#include "math/Vec2.h"

RigidBody::RigidBody(Properties properties, LinearState linearState, AngularState angularState)
{
    mass = properties.mass;
    invMass = 1 / properties.mass;
    restitution = properties.restitution;
    friction = properties.friction;

    velocity = linearState.velocity;
    acceleration = linearState.acceleration;
    netForce = linearState.netForce;

    inertia = properties.inertia;
    invInertia = 1 / properties.inertia;

    angularVelocity = angularState.angularVelocity;
    angularAcceleration = angularState.angularAcceleration;

    torque = angularState.torque;
}

RigidBody::~RigidBody()
{
}


void RigidBody::SetMass(float m)
{
    mass = m;
    invMass = 1 / m;
}

void RigidBody::ApplyForce(Vec2 force)
{
    netForce += force;
}

void RigidBody::ClearForces() 
{
    netForce = Vec2();
}

void RigidBody::ClearTorque()
{
    torque = 0.0f;
}