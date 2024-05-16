#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <stdio.h>
#include "../lib/whgmath.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *g_window = NULL;
SDL_Surface *g_screenSurface = NULL;
SDL_Renderer *g_renderer = NULL;

class Player {
public:
  const float MOVEMENT_SPEED = 500.0f;
  const float PLAYER_SIZE = 50.0f;
  const float OUTLINE_WIDTH = 10.0f;

  void process(float deltaTime) {
    move(deltaTime);

    // printf("Pos(%f/%f), Vel(%f/%f)\n", _position.x, _position.y, _velocity.x, _velocity.y);

    float outlineSize = PLAYER_SIZE + OUTLINE_WIDTH;

    SDL_FRect playerOutlineRect = {_position.x - OUTLINE_WIDTH / 2,
                                  _position.y - OUTLINE_WIDTH / 2, outlineSize,
                                  outlineSize};
    SDL_SetRenderDrawColor(g_renderer, 0x75, 0x00, 0x00, 0xff);
    SDL_RenderFillRectF(g_renderer, &playerOutlineRect);

    SDL_FRect playerRect = {_position.x, _position.y, 50, 50};
    SDL_SetRenderDrawColor(g_renderer, 0xfe, 0x00, 0x00, 0xff);
    SDL_RenderFillRectF(g_renderer, &playerRect);
  }

  void processMovement(SDL_Event &e) {
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

  void move(float deltaTime) {
    Vector2 velocity = Vector2(_velocity * deltaTime).normalized();
    velocity = velocity * MOVEMENT_SPEED;
    _position = _position + velocity;
  }

private:
  Vector2 _position = Vector2(0.0f, 0.0f);
  Vector2 _velocity = Vector2(0.0f, 0.0f);
};

bool init() {
  /* Initialize defaults, Video and Audio */
  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)) {
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    return false;
  }

  // Create SDL Window
  g_window = SDL_CreateWindow("World Hardest Game++", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  // Check if window throws error
  if (g_window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Create SDL Renderer
  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

  // Check for errors on creation
  if (g_renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  // Create ScreenSurface
  g_screenSurface = SDL_GetWindowSurface(g_window);

  // Set initial background color
  SDL_FillRect(g_screenSurface, NULL,
               SDL_MapRGB(g_screenSurface->format, 0xb0, 0xa4, 0xfc));

  SDL_UpdateWindowSurface(g_window);
  return true;
}

void close() {
  printf("Quiting SDL.\n");

  SDL_DestroyWindow(g_window);
  g_window = NULL;

  /* Shutdown all subsystems */
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  printf("Initializing SDL.\n");

  if (!init()) {
    exit(-1);
  }

  Player *player = new Player();

  SDL_Event e;
  bool quit = false;
  uint32_t lastTicks = SDL_GetTicks();
  while (!quit) {

    uint32_t nowTicks = SDL_GetTicks();

    float deltaTime = (nowTicks - lastTicks) * 0.001f;
    lastTicks = nowTicks;

    // Consume all events in the queue
    while (SDL_PollEvent(&e) != 0) {
      // Called when user Xs out the window
      if (e.type == SDL_QUIT)
        quit = true;
      else {
        player->processMovement(e);
      }
    }

    // Render a blank frame to reset the screen
    SDL_SetRenderDrawColor(g_renderer, 0xb0, 0xa4, 0xfc, 0xff);
    SDL_RenderClear(g_renderer);

    player->process(deltaTime);

    // Render frame
    SDL_RenderPresent(g_renderer);
  }

  close();

  exit(0);
}