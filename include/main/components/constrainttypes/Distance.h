#pragma once
#include "math/Vec2.h"
#include "main/components/Constraint.h"

class GameObject;

class DistanceConstraint : public Constraint
{
    public:
        GameObject* anchor;
        GameObject* attached;
        float length;

        DistanceConstraint(GameObject* anchor, GameObject* attached, float length);
        ConstraintType GetType() const override;
        void Solve(float dt) override;
};