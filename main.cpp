#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    printf("Initializing SDL.\n");

    /* Initialize defaults, Video and Audio */
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

    printf("SDL initialized.\n");

    

    printf("Quiting SDL.\n");

    /* Shutdown all subsystems */
    SDL_Quit();

    printf("Quiting....\n");

    exit(0);
}

