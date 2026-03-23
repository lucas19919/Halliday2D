#include "main/components/TransformComponent.h"

TransformComponent::TransformComponent(GameObject* parentObj)
{
    parent = parentObj;
    position = Vec2();
    rotation = 0.0f;
}