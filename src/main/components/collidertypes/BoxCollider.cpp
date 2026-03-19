#include "main/components/collidertypes/BoxCollider.h"

BoxCollider::BoxCollider(Vec2 size) : size(size) {}

ColliderType BoxCollider::getType() const
{
    return ColliderType::BOX;
}