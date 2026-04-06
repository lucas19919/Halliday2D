#pragma once
#include "math/Vec2.h"
#include "main/components/Constraint.h"
#include <vector>

class GameObject;

struct JointAttachment
{
    GameObject* obj;
    Vec2 localAnchor;
};

class JointConstraint : public Constraint
{
    public:
        std::vector<JointAttachment> attachments;

        JointConstraint(const std::vector<JointAttachment>& attachments);
        ConstraintType GetType() const override;
        void Solve(float dt) override;
};