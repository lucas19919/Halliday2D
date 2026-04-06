#pragma once
#include "math/Vec2.h"
#include "main/components/Constraint.h"
#include <vector>

class GameObject;

class JointConstraint : public Constraint
{
    public:
        std::vector<GameObject*> connectedObjects;

        JointConstraint(const std::vector<GameObject*>& objects);
        ConstraintType GetType() const override;
};
