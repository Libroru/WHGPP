//
// Created by user on 17.05.24.
//

#include "player.hpp"
#include <SDL2/SDL_render.h>

void Player::process(float deltaTime, SDL_Renderer *renderer) {
    move(deltaTime);

    // printf("Pos(%f/%f), Vel(%f/%f)\n", _position.x, _position.y, _velocity.x, _velocity.y);

    float outlineSize = PLAYER_SIZE + OUTLINE_WIDTH;

    SDL_FRect playerOutlineRect = {_position.x - OUTLINE_WIDTH / 2,
                                  _position.y - OUTLINE_WIDTH / 2, outlineSize,
                                  outlineSize};
    SDL_SetRenderDrawColor(renderer, 0x75, 0x00, 0x00, 0xff);
    SDL_RenderFillRectF(renderer, &playerOutlineRect);

    SDL_FRect playerRect = {_position.x, _position.y, 50, 50};
    SDL_SetRenderDrawColor(renderer, 0xfe, 0x00, 0x00, 0xff);
    SDL_RenderFillRectF(renderer, &playerRect);
}

void Player::processMovement(SDL_Event &e) {
    // Using a key.repeat of 0 here,
    // because we don't want multiple inputs in here
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                _velocity.y -= 1.0f;
            break;
            case SDLK_s:
                _velocity.y += 1.0f;
            break;
            case SDLK_a:
                _velocity.x -= 1.0f;
            break;
            case SDLK_d:
                _velocity.x += 1.0f;
            break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                _velocity.y += 1.0f;
            break;
            case SDLK_s:
                _velocity.y -= 1.0f;
            break;
            case SDLK_a:
                _velocity.x += 1.0f;
            break;
            case SDLK_d:
                _velocity.x -= 1.0f;
            break;
        }
    }
};

void Player::move(float deltaTime) {
    Vector2 velocity = Vector2(_velocity * deltaTime).normalized();
    velocity = velocity * MOVEMENT_SPEED;
    _position = _position + velocity;
}