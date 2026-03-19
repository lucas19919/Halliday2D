#pragma once
#include "main/components/collidertypes/BoxCollider.h"
#include "main/components/collidertypes/CircleCollider.h"
#include "main/components/collidertypes/PolygonCollider.h"

class GameObject;

enum ColliderType { BOX, CIRCLE };

class Collider
{
    public:
        virtual ~Collider() = default;
        virtual ColliderType getType() const = 0;

        GameObject* parent;
    };