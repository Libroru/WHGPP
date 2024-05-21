//
// Created by user on 20.05.24.
//

#ifndef ROTATING_BALLS_H
#define ROTATING_BALLS_H
#include <SDL_render.h>
#include <math/vectors.h>

class RotatingBalls {
public:
    const float ROTATION_SPEED = 1.0f;
    const int BALL_SIZE = 15;
    const float BALL_DISTANCE = 30.0f;

    void Rotate();
    void Render(SDL_Renderer* renderer, Vector2 location);
private:
    Vector2 location = Vector2::null();
    float rotationInDegrees = 0;
};

#endif //ROTATING_BALLS_H
