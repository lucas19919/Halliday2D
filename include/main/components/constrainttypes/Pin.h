#pragma once
#include "math/Vec2.h"
#include "main/components/Constraint.h"
#include <vector>

class GameObject;

class PinConstraint : public Constraint
{
    public:
        std::vector<GameObject*> connectedObjects;

        bool fixedX = true;
        bool fixedY = true;

        void SetFixedAxes(bool x, bool y) { fixedX = x; fixedY = y; }

        PinConstraint(const std::vector<GameObject*>& objects, bool fixedX, bool fixedY);
        ConstraintType GetType() const override;
};
