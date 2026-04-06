#pragma once
#include "math/Vec2.h"

struct Config
{
    
    int screenWidth = 1280;          
    int screenHeight = 960;          
    int targetFPS = 60;              

    Vec2 gravity = Vec2(0.0f, 600.0f);
    float spatialHashCellSize = 50.0f;
    
    int impulseIterations = 8;               
    int positionIterations = 1;              

    bool warmStart = true;

    float restitutionThreshold = 15.0f; //10-15 best for now

    float contactSlop = 0.15f;        
    float positionCorrectionPercent = 0.1f; 

    //constraints
    float biasConstraint = 0.2f; 

    //sleep
    float energyThreshold = 15.0f;
    float velocitySleepThreshold = 10.0f;
    float sleepTime = 0.5f;
    bool debugSleep = true; //different color for sleeping obj

    float generatorJitterRange = 4.0f;
};