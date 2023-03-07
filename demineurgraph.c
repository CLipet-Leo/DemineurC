#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // <cstdbool> en C++


//The window we'll be rendering to
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Surface* screenSurface = NULL;
//The image we will load and show on the screen
SDL_Surface* tile = NULL;


bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("SDL Tests", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    tile = SDL_LoadBMP("../../img/tile.bmp");
    if (tile == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "../../img/tile.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(tile);
    tile = NULL;

    //Destroy window
    SDL_DestroyWindow(tile);
    tile = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}



int main(int argc, char* argv[]) {
    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Apply the image
            SDL_BlitSurface(tile, NULL, screenSurface, NULL);
            //Update the surface
            SDL_UpdateWindowSurface(window);
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
