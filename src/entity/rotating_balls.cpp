#include "rotating_balls.h"

#include <SDL_render.h>
#include <math/vectors.h>
#include <cmath>

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    int32_t x = radius - 1;
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = tx - (radius * 2);

    while (x >= y)
    {
        // Draw horizontal lines between the points on each octant
        SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX + x, centreY - y);
        SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX + y, centreY - x);
        SDL_RenderDrawLine(renderer, centreX - x, centreY + y, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX - y, centreY + x, centreX + y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - (radius * 2));
        }
    }
}

void RotatingBalls::Rotate() {
    rotationInDegrees += ROTATION_SPEED;
}

void SpawnBall(SDL_Renderer* renderer, const Vector2 location, int ball_size) {
    DrawCircle(renderer, static_cast<int32_t>(location.x), static_cast<int32_t>(location.y), ball_size);
}

void SpawnBallAtAngle(SDL_Renderer* renderer, const Vector2 location, float angle, float distance, int ball_size) {
    const auto radians = static_cast<float>(angle * (M_PI / 180.0f));
    const float x = location.x + distance * cos(radians);
    const float y = location.y + distance * sin(radians);
    SpawnBall(renderer, Vector2(x, y), ball_size);
}

void RotatingBalls::Render(SDL_Renderer* renderer, const Vector2 location) {
    float ball_distances[] = {BALL_DISTANCE, BALL_DISTANCE * 2};

    SpawnBall(renderer, location, BALL_SIZE);
    for (const float distance : ball_distances) {
        SpawnBallAtAngle(renderer, location, rotationInDegrees, distance, BALL_SIZE);
        SpawnBallAtAngle(renderer, location, rotationInDegrees + 90.0f, distance, BALL_SIZE);
        SpawnBallAtAngle(renderer, location, rotationInDegrees + 180.0f, distance, BALL_SIZE);
        SpawnBallAtAngle(renderer, location, rotationInDegrees + 270.0f, distance, BALL_SIZE);
    }

    Rotate();
}
