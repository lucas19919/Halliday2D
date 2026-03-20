#include "main/physics/CollisionHandler.h"
#include "main/physics/SAT.h"
#include "main/components/Collider.h"


Collision CollisionHandler::SortCollision(Collider* c1, Collider* c2)
{
    if (c1->GetType() == ColliderType::CIRCLE && c2->GetType() == ColliderType::CIRCLE) {
        return SAT::CircleCircle(c1, c2);
    }
    else if (c1->GetType() == ColliderType::BOX && c2->GetType() == ColliderType::BOX) {
        return SAT::BoxBox(c1, c2);
    }
    else if (c1->GetType() == ColliderType::BOX && c2->GetType() == ColliderType::CIRCLE) {
        return SAT::BoxCircle(c1, c2);
    }
    /*else if (c1->GetType() == ColliderType::POLYGON && c2->GetType() == ColliderType::CIRCLE) {
        return SAT::PolygonCircle(c1, c2);
    }
    else if (c1->GetType() == ColliderType::POLYGON && c2->GetType() == ColliderType::BOX) {
        return SAT::PolygonBox(c1, c2);
    }
    else if (c1->GetType() == ColliderType::POLYGON && c2->GetType() == ColliderType::POLYGON) {
        return SAT::PolygonPolygon(c1, c2);
    }*/
    else if (c1->GetType() == ColliderType::CIRCLE && c2->GetType() == ColliderType::BOX) {
        Collision col = SAT::BoxCircle(c2, c1);
        col.normal = Vec2(-col.normal.x, -col.normal.y);
        return col;
    }

    return { false, Vec2(), 0.0f };
}