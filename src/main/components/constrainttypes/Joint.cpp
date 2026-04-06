#include "main/components/constrainttypes/Joint.h"
#include "main/components/Constraint.h"

JointConstraint::JointConstraint(const std::vector<GameObject*>& objects) : connectedObjects(objects)
{ }

ConstraintType JointConstraint::GetType() const
{
    return ConstraintType::JOINT;
}