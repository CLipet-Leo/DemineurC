#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // <cstdbool> en C++

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


int main(int argc, char* argv[]) {

    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //Create a render for the table
    SDL_Renderer* renderer = NULL;
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    //The image we will load and show on the screen
    SDL_Surface* tile = NULL;
    //Create a texture to duplicate
    SDL_Texture* texture = NULL;

    int statut = EXIT_FAILURE;

    bool JEU[10][10];
    int x, y;//x les lignes, y les colonnes

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        goto Quit;
    }
    else
    {
        if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            goto Quit;
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    //Load splash image
    tile = SDL_LoadBMP("../../img/background2.bmp");
    if (tile == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "../../img/background2.bmp", SDL_GetError());
        goto Quit;
    }

    //Create a texture with the BMP file
    texture = SDL_CreateTextureFromSurface(renderer, tile);
    SDL_FreeSurface(tile);
    if (texture == NULL)
    {
        printf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    SDL_Rect rectangle;

    if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
    {
        printf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

    if (SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0)
    {
        printf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    SDL_RenderPresent(renderer);


    //Hack to get window to stay up
    SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
    statut = EXIT_SUCCESS;

Quit:
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
    return statut;
}