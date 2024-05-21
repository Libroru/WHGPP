#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <cstdio>
#include <entity/player.h>
#include <entity/rotating_balls.h>
#include "core/game_manager.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

SDL_Window *g_window = nullptr;
SDL_Surface *g_screenSurface = nullptr;
SDL_Renderer *g_renderer = nullptr;

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
  if (g_window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Create SDL Renderer
  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // Check for errors on creation
  if (g_renderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  // Create ScreenSurface
  g_screenSurface = SDL_GetWindowSurface(g_window);

  // Set initial background color
  SDL_FillRect(g_screenSurface, nullptr,
               SDL_MapRGB(g_screenSurface->format, 0xb0, 0xa4, 0xfc));

  SDL_UpdateWindowSurface(g_window);
  return true;
}

void close() {
  printf("Quiting SDL.\n");

  SDL_DestroyWindow(g_window);
  g_window = nullptr;

  /* Shutdown all subsystems */
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  printf("Initializing SDL.\n");

  if (!init()) {
    exit(-1);
  }

  printf("Successfully initialized SDL.\n");

  auto *player = new Player();
  auto *rotating_balls = new RotatingBalls();

  SDL_Event e;
  bool quit = false;
  uint32_t lastTicks = SDL_GetTicks();
  while (!quit) {
    GameManager game_manager = GameManager();
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

    player->process(deltaTime, g_renderer);
    rotating_balls->Render(g_renderer, Vector2(200.0f, 200.0f));


    // Render frame
    SDL_RenderPresent(g_renderer);
  }

  close();

  exit(0);
}