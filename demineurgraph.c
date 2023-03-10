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
    //Create a grid to stock images
    SDL_Texture* stock[10];
    //Create a grid to print game
    SDL_Texture* JEU[10][10];
    //Create a grid to print game
    int MINE[10][10];

    int statut = EXIT_FAILURE;

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

    /*------------------------------------------*/
    //Load splash image
    tile = SDL_LoadBMP("../../img/tile.bmp");
    if (tile == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "../../img/tile.bmp", SDL_GetError());
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
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = (WINDOW_WIDTH / 10);
    rectangle.h = (WINDOW_HEIGHT / 10);

    stock[0] = texture;

    for (x = 0; x < 10; x++)
    {
        for (y = 0; y < 10; y++)
        {
            //affiche la grille de jeu avec des textures
            if (JEU[x - 1][y] == stock[0] || (y != 0 && JEU[x][y - 1] == stock[0])) {
                JEU[x][y] = stock[1];
            }
            else {
                JEU[x][y] = stock[0];
            }
            MINE[x][y] = 0;//définis la grille de mine avec des 0
        }
    }

    /*------------------------------------------*/
    SDL_bool program_lanched = SDL_TRUE;

    while (program_lanched)
    {
        //EVENT
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                printf("Clic en %dx/%dy\n", event.button.x, event.button.y);
                if (event.button.button == SDL_BUTTON_LEFT)
                    printf("Clic gauche\n");
                if (event.button.button == SDL_BUTTON_RIGHT)
                    printf("Clic droit\n");
                break;

            case SDL_QUIT:
                program_lanched = SDL_FALSE;
                break;

            default:
                continue;
            }
        }
        //UPDATE

        //RENDER
        //clear
        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
        SDL_RenderClear(renderer);
        //draw
        for (x = 0; x < 10; x++)
        {
            rectangle.x = 0 + (WINDOW_WIDTH / 10) * x;
            for (y = 0; y < 10; y++)
            {
                rectangle.y = 0 + (WINDOW_HEIGHT / 10) * y;
                if (SDL_RenderCopy(renderer, JEU[x][y], NULL, &rectangle) != 0)
                {
                    printf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
                    goto Quit;
                }
            }
        }
        //renderpresent
        SDL_RenderPresent(renderer);
    }
    /*------------------------------------------*/

    statut = EXIT_SUCCESS;

Quit:
    if (NULL != texture)
        SDL_DestroyTexture(texture);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
    return statut;
}