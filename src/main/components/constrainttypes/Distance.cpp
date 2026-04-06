#include "main/components/constrainttypes/Distance.h"
#include "main/components/Constraint.h"
#include "main/World.h"
#include "main/physics/Config.h"


DistanceConstraint::DistanceConstraint(GameObject* anchor, GameObject* attached, float length) : anchor(anchor), attached(attached), length(length)
{ }

ConstraintType DistanceConstraint::GetType() const
{
    return ConstraintType::DISTANCE;
}

void DistanceConstraint::Solve(float dt)
{
    RigidBody* rb1 = anchor->GetRigidBody();
    RigidBody* rb2 = attached->GetRigidBody();

    float invMass1 = (rb1) ? rb1->GetInvMass() : 0.0f;
    float invMass2 = (rb2) ? rb2->GetInvMass() : 0.0f;

    if (invMass1 == 0.0f && invMass2 == 0.0f) return;

    Vec2 delta = attached->transform.position - anchor->transform.position;
    float currentLength = delta.Mag();
    if (currentLength < 0.0001f) return;
    
    if (currentLength < length) return; 

    Vec2 axis = delta * (1.0f / currentLength);
    float error = currentLength - length;

    Vec2 v1 = rb1 ? rb1->GetVelocity() : Vec2(0,0);
    Vec2 v2 = rb2 ? rb2->GetVelocity() : Vec2(0,0);
    float relative = axis.Dot(v2 - v1);

    float totalInvMass = invMass1 + invMass2;

    float bias = (Config().biasConstraint / dt) * error;

    float lambda = -(relative + bias) / totalInvMass;
    accumulatedImpulse += lambda;

    Vec2 impulse = axis * lambda;

    if (rb1) rb1->SetVelocity(rb1->GetVelocity() - impulse * invMass1);
    if (rb2) rb2->SetVelocity(rb2->GetVelocity() + impulse * invMass2);

    position = (anchor->transform.position + attached->transform.position) * 0.5f;
}