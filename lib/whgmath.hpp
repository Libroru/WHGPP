#ifndef WHGMATH_HPP
#define WHGMATH_HPP

#pragma once

struct Vector2 {
public:
    float x;
    float y;

    Vector2(float _posX, float _posY);
    Vector2 normalized();
    Vector2 operator* (float value);
    Vector2 operator+ (Vector2 &vector2);
};

#endif // WHGMATH_HPP
