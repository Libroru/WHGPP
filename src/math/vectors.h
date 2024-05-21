#ifndef VECTORS_HPP
#define VECTORS_HPP

#pragma once

struct Vector2 {
public:
    float x;
    float y;

    enum Direction {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };

    Vector2(float _posX, float _posY);
    [[nodiscard]] static Vector2 null();
    [[nodiscard]] Vector2 normalized() const;
    Vector2 operator* (float value) const;
    Vector2 operator+ (Vector2 &vector2) const;
};

#endif // VECTORS_HPP
