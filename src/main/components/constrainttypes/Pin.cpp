#include "main/components/constrainttypes/Pin.h"
#include "main/components/Constraint.h"
#include "main/World.h"
#include "main/physics/Config.h"

PinConstraint::PinConstraint(const std::vector<PinAttachment>& attachments, bool fixedX, bool fixedY)
    : attachments(attachments), fixedX(fixedX), fixedY(fixedY)
{ }

ConstraintType PinConstraint::GetType() const
{
    return ConstraintType::PIN;
}

void PinConstraint::Solve(float dt)
{
    float biasConstraint = Config().biasConstraint;

    for (auto& att : attachments)
    {
        RigidBody* rb = att.obj->GetRigidBody();
        if (!rb) continue;

        float invMass = rb->GetInvMass();
        if (invMass == 0.0f) continue;

        float s = sinf(att.obj->transform.rotation);
        float c = cosf(att.obj->transform.rotation);
        Vec2 rotatedAnchor = Vec2(
            att.localAnchor.x * c - att.localAnchor.y * s,
            att.localAnchor.x * s + att.localAnchor.y * c
        );

        Vec2 worldAnchor = att.obj->transform.position + rotatedAnchor;
        Vec2 delta = worldAnchor - position;

        Vec2 vel = rb->GetVelocity();

        if (fixedX)
        {
            float bias = (biasConstraint / dt) * delta.x;
            float impulse = -(vel.x + bias) / invMass;
            vel.x += impulse * invMass;
        }

        if (fixedY)
        {
            float bias = (biasConstraint / dt) * delta.y;
            float impulse = -(vel.y + bias) / invMass;
            vel.y += impulse * invMass;
        }

        rb->SetVelocity(vel);
    }

    if (!attachments.empty())
    {
        auto& first = attachments[0];
        float sin = sinf(first.obj->transform.rotation);
        float cos = cosf(first.obj->transform.rotation);
        Vec2 rotatedAnchor = Vec2(
            first.localAnchor.x * cos - first.localAnchor.y * sin,
            first.localAnchor.x * sin + first.localAnchor.y * cos
        );
        Vec2 worldAnchor = first.obj->transform.position + rotatedAnchor;

        if (!fixedX) position.x = worldAnchor.x;
        if (!fixedY) position.y = worldAnchor.y;
    }
}