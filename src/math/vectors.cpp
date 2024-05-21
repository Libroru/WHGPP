#include "vectors.h"

Vector2::Vector2(float _posX, float _posY) {
    x = _posX;
    y = _posY;
}

Vector2 Vector2::null() {
    return {0, 0};
}

Vector2 Vector2::normalized() const {
    float x = this->x / 2;
    float y = this->y / 2;
    return {x, y};
}

Vector2 Vector2::operator* (float value) const {
    float x = this->x * value;
    float y = this->y * value;
    return {x, y};
}

Vector2 Vector2::operator+ (Vector2 &vector2) const {
    float x = this->x + vector2.x;
    float y = this->y + vector2.y;
    return {x, y};
}
