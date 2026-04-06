#include "main/components/constrainttypes/Pin.h"
#include "main/components/Constraint.h"

PinConstraint::PinConstraint(const std::vector<GameObject*>& objects, bool fixedX, bool fixedY) : connectedObjects(objects), fixedX(fixedX), fixedY(fixedY)
{ }

ConstraintType PinConstraint::GetType() const
{
    return ConstraintType::PIN;
}