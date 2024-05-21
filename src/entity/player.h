//
// Created by user on 17.05.24.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "../math/vectors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class Player {
public:
    const float MOVEMENT_SPEED = 500.0f;
    const float PLAYER_SIZE = 35.0f;
    const float OUTLINE_WIDTH = 5.0f;

    void process(float deltaTime, SDL_Renderer *renderer);

    void processMovement(SDL_Event &e);

    void move(float deltaTime);

private:
    Vector2 _position = Vector2(0.0f, 0.0f);
    Vector2 _velocity = Vector2(0.0f, 0.0f);
};

#endif //PLAYER_H
