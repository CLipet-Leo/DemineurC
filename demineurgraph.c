#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int SDL_Init(Uint32 flags);
void SDL_Quit(void);
const char* SDL_GetError(void);
void SDL_Delay(Uint32 ms);



int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    int statut = EXIT_FAILURE;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("Deminator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    if (NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    statut = EXIT_SUCCESS;
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
Quit:
    SDL_Quit();
    return statut;
}
