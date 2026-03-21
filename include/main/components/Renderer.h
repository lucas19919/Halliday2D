#pragma once
#include "raylib.h"
#include <vector>
#include "math/Vec2.h"

class GameObject;

class Renderer
{
    public:
        Renderer(Color c);
        ~Renderer() = default;

        GameObject *parent;

        Color color = RED;
};