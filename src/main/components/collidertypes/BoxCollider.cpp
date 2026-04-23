#include "main/components/collidertypes/BoxCollider.h"
#include <cmath>

BoxCollider::BoxCollider(Vec2 size) : size(size) {}

ColliderType BoxCollider::GetType() const
{
    return ColliderType::BOX;
}

#include "math/RotationMatrix.h"

void BoxCollider::UpdateCache(const TransformComponent& transform)
{
    cachedVertices.count = 0;
    cachedNormals.count = 0;

    float x = size.x / 2.0f;
    float y = size.y / 2.0f;
    
    Vec2 local[4] = {
        Vec2(-x, -y), Vec2( x, -y), Vec2( x,  y), Vec2(-x,  y)
    };

    RotMatrix rot(transform.rotation);

    for (int i = 0; i < 4; i++)
    {
        Vec2 rotated = rot.Rotate(local[i]);
        cachedVertices.PushBack(rotated + transform.position);
    }

    // Update normals
    for (size_t i = 0; i < 4; i++)
    {
        Vec2 edge = cachedVertices[(i + 1) % 4] - cachedVertices[i];
        Vec2 normal = Vec2(edge.y, -edge.x);
        cachedNormals.PushBack(normal.Norm());
    }
}

bool BoxCollider::IsPointInside(Vec2 point) const
{
    if (cachedVertices.Size() < 3) return false;

    for (size_t i = 0; i < cachedVertices.Size(); i++)
    {
        Vec2 p1 = cachedVertices[i];
        Vec2 p2 = cachedVertices[(i + 1) % cachedVertices.Size()];
        
        Vec2 edge = p2 - p1;
        Vec2 toPoint = point - p1;
        
        // cross product in 2D
        float cross = edge.x * toPoint.y - edge.y * toPoint.x;
        if (cross < 0) return false; 
    }
    return true;
}