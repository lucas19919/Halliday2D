#include "main/components/collidertypes/CircleCollider.h"

CircleCollider::CircleCollider(float radius) : radius(radius) {}

ColliderType CircleCollider::getType() const
{
    return ColliderType::CIRCLE;
}