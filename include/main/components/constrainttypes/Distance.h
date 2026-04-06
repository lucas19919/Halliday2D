#pragma once
#include "math/Vec2.h"
#include "main/components/Constraint.h"

class GameObject;

class DistanceConstraint : public Constraint
{
    public:
        GameObject* obj1;
        GameObject* obj2;
        float length;

        DistanceConstraint(GameObject* o1, GameObject* o2, float length);
        ConstraintType GetType() const override;
};