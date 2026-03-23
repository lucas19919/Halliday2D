#include "main/utility/Draw.h"
#include "main/components/Collider.h"
#include "main/components/Renderer.h"
#include "main/components/collidertypes/BoxCollider.h"
#include "main/components/collidertypes/CircleCollider.h"

void Render(GameObject *obj)
{
    if (obj->GetRenderer() == nullptr) return;

    Renderer *r = obj->GetRenderer();
    Shape shape = r->GetShape();

    switch (shape.form)
    {
    case RenderShape::R_CIRCLE:
        DrawCircle(obj->transform.position.x, obj->transform.position.y, shape.scale.radius, shape.color);
        break;
    case RenderShape::R_BOX:
    {
        Vec2 size = shape.scale.size;
        DrawRectanglePro(
            Rectangle{ obj->transform.position.x, obj->transform.position.y, size.x, size.y },
            { size.x / 2.0f, size.y / 2.0f },
            obj->transform.rotation * RAD2DEG,
            shape.color
        );        

        break;
    }
    default:
        break;
    }
}