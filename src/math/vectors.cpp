#include "vectors.hpp"

Vector2::Vector2(float _posX, float _posY) {
    x = _posX;
    y = _posY;
}

Vector2 Vector2::normalized() {
    float x = this->x / 2;
    float y = this->y / 2;
    return Vector2(x, y);
}

Vector2 Vector2::operator* (float value) {
    float x = this->x * value;
    float y = this->y * value;
    return Vector2(x, y);
}

Vector2 Vector2::operator+ (Vector2 &vector2) {
    float x = this->x + vector2.x;
    float y = this->y + vector2.y;
    return Vector2(x, y);
}
