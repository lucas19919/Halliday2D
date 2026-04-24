#pragma once
#include "raylib.h"
#include "math/Vec2.h"

class EditorCamera {
public:
    EditorCamera(float screenWidth, float screenHeight);

    void Begin();
    void End();

    void Pan(Vector2 delta);
    void Zoom(float delta, Vector2 mousePos);

    Vec2 ScreenToWorldMeters(Vector2 screenPos) const;
    Vector2 WorldToScreenPixels(Vec2 worldPos) const;

    const Camera2D& GetRaylibCamera() const { return camera; }
    Camera2D& GetRaylibCamera() { return camera; }

private:
    Camera2D camera;
};
