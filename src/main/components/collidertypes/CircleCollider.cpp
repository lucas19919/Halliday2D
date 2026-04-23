#include "main/components/collidertypes/CircleCollider.h"
#include "main/components/Collider.h"
#include "main/components/TransformComponent.h"

CircleCollider::CircleCollider(float radius) : radius(radius) {}

ColliderType CircleCollider::GetType() const
{
    return ColliderType::CIRCLE;
}

void CircleCollider::UpdateCache(const TransformComponent& transform)
{
    cachedVertices.Clear();
    cachedVertices.PushBack(transform.position);
}

bool CircleCollider::IsPointInside(Vec2 point) const
{
    if (cachedVertices.Size() == 0) return false;
    Vec2 center = cachedVertices[0];
    return (point - center).MagSq() <= radius * radius;
}
