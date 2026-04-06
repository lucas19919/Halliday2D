#include "main/components/constrainttypes/Distance.h"
#include "main/components/Constraint.h"


DistanceConstraint::DistanceConstraint(GameObject* obj1, GameObject* obj2, float length) : obj1(obj1), obj2(obj2), length(length)
{ }

ConstraintType DistanceConstraint::GetType() const
{
    return ConstraintType::DISTANCE;
}