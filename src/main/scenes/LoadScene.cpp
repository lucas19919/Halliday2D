#include "main/scenes/LoadScene.h"
#include <raylib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <libraries/json/json.hpp>

using json = nlohmann::json;

void LoadScene::Load(const std::string& filePath, World& world, int screenWidth, int screenHeight)
{
    world.Clear();

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Loading Scene Failed: " << filePath << std::endl;
        return;
    }

    json sceneData;
    file >> sceneData;

    if (sceneData.contains("useWalls") && sceneData["useWalls"] == true) {
        GameObject* floor = Instantiate()
            .WithTransform(Vec2(screenWidth / 2.0f, screenHeight + 25.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(screenWidth, 50.0f))
            .Create(world);

        GameObject* ceiling = Instantiate()
            .WithTransform(Vec2(screenWidth / 2.0f, -25.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(screenWidth, 50.0f))
            .Create(world);

        GameObject* leftWall = Instantiate()
            .WithTransform(Vec2(-25.0f, screenHeight / 2.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(50.0f, screenHeight))
            .Create(world);

        GameObject* rightWall = Instantiate()
            .WithTransform(Vec2(screenWidth + 25.0f, screenHeight / 2.0f), 0.0f)
            .WithCollider(ColliderType::BOX, Vec2(50.0f, screenHeight))
            .Create(world);
    }

    for (const auto& item : sceneData["objects"]) 
    {
        if (!item.contains("components")) continue;
        const auto& components = item["components"];

        float x;
        float y;
        float rot;

        if (components.contains("TransformComponent"))
        {
            x = components["TransformComponent"]["position"]["x"];
            y = components["TransformComponent"]["position"]["y"];
            rot = components["TransformComponent"]["rotation"];
        }

        ColliderType collider;
        Vec2 size;
        float radius = 0.0f;
        std::vector<Vec2> polyVerts;
        
        if (components.contains("Collider"))
        {
            std::string type = components["Collider"]["type"];
            if (type == "BOX")
            {
                collider = ColliderType::BOX;
                size.x = components["Collider"]["size"]["x"];
                size.y = components["Collider"]["size"]["y"];
            }
            else if (type == "CIRCLE")
            {
                collider = ColliderType::CIRCLE;
                radius = components["Collider"]["radius"];
            }
            else if (type == "POLYGON")
            {
                collider = ColliderType::POLYGON;
                for (const auto& v : components["Collider"]["vertices"])
                {
                    polyVerts.push_back(Vec2(v["x"], v["y"]));
                }
            }
        }

        Shape renderShape;
        if (components.contains("Renderer"))
        {
            std::string form = components["Renderer"]["form"];
            std::string colorStr = components["Renderer"]["color"];

            Color col = GRAY;
            if (colorStr == "RED") col = RED;
            else if (colorStr == "GREEN") col = GREEN;
            else if (colorStr == "BLUE") col = BLUE;

            renderShape.color = col;

            if (form == "R_BOX")
            {
                renderShape.form = RenderShape::R_BOX;
                size = Vec2(components["Renderer"]["scale"]["x"], components["Renderer"]["scale"]["y"]);
                renderShape.scale = size;
            }
            else if (form == "R_CIRCLE")
            {
                renderShape.form = RenderShape::R_CIRCLE;
                renderShape.scale = components["Renderer"]["scale"];
            }
            else if (form == "R_POLYGON")
            {
                renderShape.form = RenderShape::R_POLYGON;
                std::vector<Vec2> pVertices;
                for (const auto& v : components["Renderer"]["scale"])
                {
                    pVertices.push_back(Vec2(v["x"], v["y"]));
                }

                renderShape.scale = pVertices;
            }
        }

        Properties props;
        LinearState linear;
        AngularState angular;

        if (components.contains("RigidBody"))
        {
            props.mass = components["RigidBody"]["properties"]["mass"];
            props.restitution = components["RigidBody"]["properties"]["restitution"];
            props.friction = components["RigidBody"]["properties"]["friction"];
            props.inertia = components["RigidBody"]["properties"]["inertia"];

            linear.velocity.x = components["RigidBody"]["linearState"]["velocity"]["x"];
            linear.velocity.y = components["RigidBody"]["linearState"]["velocity"]["y"];
            linear.acceleration.x = components["RigidBody"]["linearState"]["acceleration"]["x"];
            linear.acceleration.y = components["RigidBody"]["linearState"]["acceleration"]["y"];
            linear.netForce.x = components["RigidBody"]["linearState"]["netForce"]["x"];
            linear.netForce.y = components["RigidBody"]["linearState"]["netForce"]["y"];

            angular.angularVelocity = components["RigidBody"]["angularState"]["angularVelocity"];
            angular.angularAcceleration = components["RigidBody"]["angularState"]["angularAcceleration"];
            angular.torque = components["RigidBody"]["angularState"]["torque"];
        }

        Instantiate& builder = Instantiate().WithTransform(Vec2(x, y), rot);

        if (collider == ColliderType::BOX)
        {
            builder.WithCollider(collider, size);
        }
        else if (collider == ColliderType::CIRCLE)
        {
            builder.WithCollider(collider, radius);
        }
        else if (collider == ColliderType::POLYGON)
        {
            builder.WithCollider(collider, polyVerts);
        }

        builder.WithRenderer(renderShape);
        builder.WithRigidBody(props, linear, angular);
        builder.Create(world);
    }
}