#include "main/components/collidertypes/PolygonCollider.h"
#include <cmath>

PolygonCollider::PolygonCollider(const Array<20>& vertices) : vertices(vertices) {}

ColliderType PolygonCollider::GetType() const
{
    return ColliderType::POLYGON;
}

#include "math/RotationMatrix.h"

void PolygonCollider::UpdateCache(const TransformComponent& transform)
{
    cachedVertices.count = 0;
    cachedNormals.count = 0;

    RotMatrix rot(transform.rotation);

    for (size_t i = 0; i < vertices.Size(); i++)
    {
        Vec2 rotated = rot.Rotate(vertices[i]);
        cachedVertices.PushBack(rotated + transform.position);
    }

    // Update normals
    for (size_t i = 0; i < cachedVertices.Size(); i++)
    {
        Vec2 edge = cachedVertices[(i + 1) % cachedVertices.Size()] - cachedVertices[i];
        Vec2 normal = Vec2(edge.y, -edge.x);
        cachedNormals.PushBack(normal.Norm());
    }
}

bool PolygonCollider::IsPointInside(Vec2 point) const
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