#include "main/utility/Instantiate.h"
#include "main/components/collidertypes/CircleCollider.h"
#include "main/components/collidertypes/BoxCollider.h"

Instantiate& Instantiate::WithRigidBody(Properties properties, LinearState linearState, AngularState angularState)
{
    obj->SetRigidBody(new RigidBody(properties, linearState, angularState));
    return *this;
}

Instantiate& Instantiate::WithRenderer(Shape shape)
{
    obj->SetRenderer(new Renderer(shape));
    return *this;
}

Instantiate& Instantiate::WithCollider(ColliderType type, Vec2 size, float radius)
{
    switch (type)
    {
    case ColliderType::CIRCLE:
        obj->SetCollider(new CircleCollider(radius));
        break;
    case ColliderType::BOX:
        obj->SetCollider(new BoxCollider(size));
        break;
    default:
        break;
    }

    return *this;
}

Instantiate& Instantiate::WithTransform(Vec2 position, float rotation)
{
    obj->transform.position = position;
    obj->transform.rotation = rotation;
    return *this;
}

GameObject* Instantiate::Create(World& world)
{
    world.AddGameObject(obj);
    return obj;
}

Instantiate::Instantiate()
{
    obj = new GameObject();
}