#pragma once
#include "math/Vec2.h"

struct Config
{
    // Window / rendering
    int screenWidth = 1280;          // src/main.cpp
    int screenHeight = 960;          // src/main.cpp
    int targetFPS = 60;              // src/main.cpp

    // World / physics
    Vec2 gravity = Vec2(0.0f, 600.0f); // World::World() sets gravity to (0,600)
    float spatialHashCellSize = 35.0f; // used to initialize spatialHash in World constructor

    // Integration / stepping
    int subSteps = 8;                // World::Step uses subTicks (renamed subSteps)

    // Collision resolution / position correction
    float contactSlop = 0.1f;        // Resolve::ResolvePosition
    float positionCorrectionPercent = 0.6f; // Resolve::ResolvePosition

    // Scene loading / generators
    float generatorJitterRange = 4.0f; // LoadScene: uniform_real_distribution(-4.0f,4.0f)

    // Debug
    bool debugSleepingStates = false; // Draw::Render, colors sleeping objects differently
};