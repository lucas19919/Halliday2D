#include "main/components/constrainttypes/Joint.h"
#include "main/components/Constraint.h"
#include "main/World.h"
#include "main/physics/Config.h"

JointConstraint::JointConstraint(const std::vector<JointAttachment>& attachments)
    : attachments(attachments)
{ }

ConstraintType JointConstraint::GetType() const
{
    return ConstraintType::JOINT;
}

void JointConstraint::Solve(float dt)
{
    float biasConstraint = Config::biasConstraint;

    Vec2 target;
    int count = 0;

    for (auto& att : attachments)
    {
        float sin = sinf(att.obj->transform.rotation);
        float cos = cosf(att.obj->transform.rotation);

        Vec2 worldAnchor = att.obj->transform.position + Vec2(
            att.localAnchor.x * cos - att.localAnchor.y * sin,
            att.localAnchor.x * sin + att.localAnchor.y * cos
        );

        target += worldAnchor;
        count++;
    }

    if (count == 0) return;
    target = target * (1.0f / count);

    for (auto& att : attachments)
    {
        RigidBody* rb = att.obj->GetRigidBody();
        if (!rb) continue;

        float invMass = rb->GetInvMass();
        if (invMass == 0.0f) continue;

        float sin = sinf(att.obj->transform.rotation);
        float cos = cosf(att.obj->transform.rotation);
        Vec2 worldAnchor = att.obj->transform.position + Vec2(
            att.localAnchor.x * cos - att.localAnchor.y * sin,
            att.localAnchor.x * sin + att.localAnchor.y * cos
        );

        Vec2 delta = worldAnchor - target;
        Vec2 vel = rb->GetVelocity();

        float biasX = (biasConstraint / dt) * delta.x;
        float lambdaX = -(vel.x + biasX) / invMass;
        vel.x += lambdaX * invMass;

        float biasY = (biasConstraint / dt) * delta.y;
        float lambdaY = -(vel.y + biasY) / invMass;
        vel.y += lambdaY * invMass;

        rb->SetVelocity(vel);
    }

    position = target;
}