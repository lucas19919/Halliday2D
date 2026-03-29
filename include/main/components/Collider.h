#pragma once
#include "math/Vec2.h"

class GameObject;

enum ColliderType { 
    CIRCLE, 
    BOX,
    POLYGON
};

struct BBox {
    Vec2 min;
    Vec2 max;
};

class Collider
{
    public:
        virtual ~Collider() = default;
        virtual ColliderType GetType() const = 0;

        BBox GetBounds() const { return bounds; }
        void SetBounds(const BBox& newBounds) { bounds = newBounds; }

        bool isActive = true;
        void Toggle();
    
    private:
            BBox bounds;

    };