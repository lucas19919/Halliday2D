#pragma once

struct Vec2 {
    float x;
    float y;

    Vec2() : x(0.0f), y(0.0f) {};
    Vec2(float xIn, float yIn) : x(xIn), y(yIn) {};

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(float scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }

    void operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }
};