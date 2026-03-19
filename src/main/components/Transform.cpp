#include "main/components/Transform.h"

Transform::Transform(GameObject* parentObj)
{
    parent = parentObj;
    position = Vec2();
    rotation = 0.0f;
    scale = Vec2(1.0f, 1.0f);
}

Transform::~Transform()
{
    
}