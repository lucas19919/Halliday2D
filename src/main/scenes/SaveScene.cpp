#include "main/scenes/SaveScene.h"
#include "main/GameObject.h"
#include "main/components/Collider.h"
#include "main/components/Renderer.h"
#include "main/components/RigidBody.h"
#include "main/components/TransformComponent.h"
#include "main/components/collidertypes/BoxCollider.h"
#include "main/components/collidertypes/CircleCollider.h"
#include "main/components/collidertypes/PolygonCollider.h"
#include "main/components/constrainttypes/Distance.h"
#include "main/components/constrainttypes/Pin.h"
#include "main/components/constrainttypes/Joint.h"
#include "main/components/constrainttypes/Motor.h"
#include "main/components/controllertypes/MotorController.h"
#include <fstream>
#include <iomanip>

using json = nlohmann::json;

static std::string ColorToString(Color color)
{
    if (color.r == 230 && color.g == 41 && color.b == 55) return "RED";
    if (color.r == 0 && color.g == 228 && color.b == 48) return "GREEN";
    if (color.r == 0 && color.g == 121 && color.b == 241) return "BLUE";
    if (color.r == 127 && color.g == 106 && color.b == 79) return "BROWN";
    if (color.r == 80 && color.g == 80 && color.b == 80) return "DARKGRAY";
    if (color.r == 253 && color.g == 249 && color.b == 0) return "YELLOW";
    if (color.r == 255 && color.g == 161 && color.b == 0) return "ORANGE";
    if (color.r == 255 && color.g == 255 && color.b == 255) return "WHITE";
    if (color.r == 0 && color.g == 0 && color.b == 0) return "BLACK";
    return "GRAY";
}

static json Vec2ToJSON(Vec2 v)
{
    return { {"x", v.x}, {"y", v.y} };
}

void SaveScene::Save(const std::string& filePath, World& world)
{
    json scene;
    scene["name"] = "Saved Scene";
    scene["worldSize"] = Vec2ToJSON(world.GetWorldSize());
    
    json objects = json::array();
    for (const auto& objPtr : world.GetGameObjects())
    {
        // Don't save walls created by LoadScene if we want to use 'useWalls' flag
        // but for now let's just save everything
        objects.push_back(SerializeObject(objPtr.get()));
    }
    scene["objects"] = objects;
    scene["constraints"] = SerializeConstraints(world.GetConstraints());
    scene["controllers"] = SerializeControllers(world.GetControllers());

    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << std::setw(4) << scene << std::endl;
    }
}

json SaveScene::SerializeObject(GameObject* obj)
{
    json j;
    j["id"] = obj->GetID();
    j["name"] = obj->GetName();
    if (!obj->GetGroupName().empty()) j["groupName"] = obj->GetGroupName();

    json components;
    
    // Transform
    components["TransformComponent"] = {
        {"position", Vec2ToJSON(obj->transform.position)},
        {"rotation", obj->transform.rotation}
    };

    // Collider
    if (obj->c)
    {
        json col;
        if (obj->c->GetType() == ColliderType::BOX)
        {
            col["type"] = "BOX";
            col["size"] = Vec2ToJSON(static_cast<BoxCollider*>(obj->c)->size);
        }
        else if (obj->c->GetType() == ColliderType::CIRCLE)
        {
            col["type"] = "CIRCLE";
            col["radius"] = static_cast<CircleCollider*>(obj->c)->radius;
        }
        else if (obj->c->GetType() == ColliderType::POLYGON)
        {
            col["type"] = "POLYGON";
            json verts = json::array();
            auto& vArr = static_cast<PolygonCollider*>(obj->c)->vertices;
            for (size_t i = 0; i < vArr.Size(); i++) verts.push_back(Vec2ToJSON(vArr[i]));
            col["vertices"] = verts;
        }
        components["Collider"] = col;
    }

    // Renderer
    Renderer* ren = obj->GetComponent<Renderer>();
    if (ren)
    {
        json r;
        Shape shape = ren->GetShape();
        r["color"] = ColorToString(shape.color);
        
        if (shape.form == RenderShape::R_BOX)
        {
            r["form"] = "R_BOX";
            r["scale"] = Vec2ToJSON(std::get<Vec2>(shape.scale));
        }
        else if (shape.form == RenderShape::R_CIRCLE)
        {
            r["form"] = "R_CIRCLE";
            r["scale"] = std::get<float>(shape.scale);
        }
        else if (shape.form == RenderShape::R_POLYGON)
        {
            r["form"] = "R_POLYGON";
            json verts = json::array();
            auto& vArr = std::get<Array<20>>(shape.scale);
            for (size_t i = 0; i < vArr.Size(); i++) verts.push_back(Vec2ToJSON(vArr[i]));
            r["scale"] = verts;
        }
        components["Renderer"] = r;
    }

    // RigidBody
    if (obj->rb)
    {
        json rb;
        rb["gravityEnabled"] = obj->rb->IsGravityEnabled();
        rb["properties"] = {
            {"mass", obj->rb->GetMass()},
            {"restitution", obj->rb->GetRestitution()},
            {"inertia", obj->rb->GetInertia()},
            {"friction", obj->rb->GetFriction()}
        };
        rb["linearState"] = {
            {"velocity", Vec2ToJSON(obj->rb->GetVelocity())},
            {"acceleration", Vec2ToJSON(obj->rb->GetAcceleration())},
            {"netForce", Vec2ToJSON(obj->rb->GetForce())}
        };
        rb["angularState"] = {
            {"angularVelocity", obj->rb->GetAngularVelocity()},
            {"angularAcceleration", obj->rb->GetAngularAcceleration()},
            {"torque", obj->rb->GetTorque()}
        };
        components["RigidBody"] = rb;
    }

    j["components"] = components;
    return j;
}

json SaveScene::SerializeConstraints(const std::vector<std::unique_ptr<Constraint>>& constraints)
{
    json arr = json::array();
    for (const auto& cPtr : constraints)
    {
        json c;
        c["id"] = cPtr->GetID();
        if (cPtr->GetType() == ConstraintType::DISTANCE)
        {
            c["type"] = "DISTANCE";
            auto* dc = static_cast<DistanceConstraint*>(cPtr.get());
            c["anchor"] = dc->anchor->GetID();
            c["attached"] = dc->attached->GetID();
            c["length"] = dc->length;
            c["anchorOffset"] = Vec2ToJSON(dc->anchorOffset);
            c["attachedOffset"] = Vec2ToJSON(dc->attachedOffset);
        }
        else if (cPtr->GetType() == ConstraintType::PIN)
        {
            c["type"] = "PIN";
            auto* pc = static_cast<PinConstraint*>(cPtr.get());
            c["position"] = Vec2ToJSON(pc->position);
            c["fixedX"] = pc->fixedX;
            c["fixedY"] = pc->fixedY;
            json atts = json::array();
            for (const auto& att : pc->attachments)
            {
                atts.push_back({ {"id", att.obj->GetID()}, {"localAnchor", Vec2ToJSON(att.localAnchor)} });
            }
            c["attachments"] = atts;
        }
        else if (cPtr->GetType() == ConstraintType::JOINT)
        {
            c["type"] = "JOINT";
            auto* jc = static_cast<JointConstraint*>(cPtr.get());
            c["position"] = Vec2ToJSON(jc->position);
            c["collisions"] = jc->collisions;
            json atts = json::array();
            for (const auto& att : jc->attachments)
            {
                atts.push_back({ {"id", att.obj->GetID()}, {"localAnchor", Vec2ToJSON(att.localAnchor)} });
            }
            c["attachments"] = atts;
        }
        else if (cPtr->GetType() == ConstraintType::MOTOR)
        {
            c["type"] = "MOTOR";
            auto* mc = static_cast<MotorConstraint*>(cPtr.get());
            c["rotor"] = mc->rotor->GetID();
            c["localPosition"] = Vec2ToJSON(mc->localPosition);
            c["torque"] = mc->torque;
        }
        arr.push_back(c);
    }
    return arr;
}

json SaveScene::SerializeControllers(const std::vector<std::unique_ptr<Controller>>& controllers)
{
    json arr = json::array();
    for (const auto& ctrlPtr : controllers)
    {
        if (ctrlPtr->GetType() == ControllerType::CNT_MOTOR)
        {
            json c;
            c["type"] = "MOTOR";
            auto* mc = static_cast<MotorController*>(ctrlPtr.get());
            c["active"] = mc->active;
            c["torqueMax"] = mc->GetTorqueMax();
            json motors = json::array();
            for (auto* m : mc->GetMotors()) motors.push_back(m->GetID());
            c["constraints"] = motors;
            arr.push_back(c);
        }
    }
    return arr;
}
