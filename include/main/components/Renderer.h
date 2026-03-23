#pragma once
#include "raylib.h"
#include <vector>
#include "math/Vec2.h"

class GameObject;

enum RenderShape {
    R_CIRCLE,
    R_BOX
};

typedef struct {
    RenderShape form;
    Color color = RED;
    union Scale
    {
        Vec2 size;
        float radius;
    } scale;
} Shape;

class Renderer
{
    public:
        Renderer(Shape shape);
        ~Renderer() = default;

        std::vector<Vec2> GetLocalCoordinates() const;
        std::vector<Vec2> GetWorldCoordinates(Vec2 position) const;
        std::vector<Vec2> UpdateWorldCoordinates(Vec2 position, float rotation);

        Shape GetShape() const { return shape; }

        GameObject *parent;
    private:
        Shape shape;
        
        std::vector<Vec2> localCoordinates;
        std::vector<Vec2> worldCoordinates;
};