#pragma once
#include "raylib.h"

class gameObject;

class Renderer
{
    public:
        Renderer() = default;
        Renderer(Color c) : color(c) {}

        GameObject* parent;

        Color color = RED;
};