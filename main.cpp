#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  printf("Initializing SDL.\n");

  /* Initialize defaults, Video and Audio */
  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)) {
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    exit(-1);
  }

  printf("SDL initialized.\n");

  printf("Initializing window\n");

  window = SDL_CreateWindow("World Hardest Game++", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(-1);
  }

  screenSurface = SDL_GetWindowSurface(window);

  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
  }

  printf("Quiting SDL.\n");

  SDL_DestroyWindow(window);

  /* Shutdown all subsystems */
  SDL_Quit();

  printf("Quiting....\n");

  exit(0);
}
