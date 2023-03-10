#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void random_mine(int MINE[10][10], int x, int y, int ligne, int colonne);
int checkMine(char JEU[10][10], int MINE[10][10], int x, int y);
void reveal(char JEU[10][10], int MINE[10][10], int x, int y, int victoire);

int main(int argc, char* argv[]) 
{
    SDL_Window* window = NULL;//The window we'll be rendering to
    SDL_Renderer* renderer = NULL;//Create a render for the table
    SDL_Surface* screenSurface = NULL;//The surface contained by the window
    //The images we will load
    SDL_Surface* tile1 = NULL;
    SDL_Surface* tile2 = NULL;
    //Create texture to duplicate
    SDL_Texture* case1 = NULL;
    SDL_Texture* case2 = NULL;
    //Create a grid to stock images
    SDL_Texture* stock[10];
    SDL_Texture* JEU[10][10];//Create a grid to print game
    int MINE[10][10];//Create a grid for the mines

    int statut = EXIT_FAILURE;

    int x, y;//x les lignes, y les colonnes
    int victoire = 90;
    int ligne, colonne;

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
            screenSurface = SDL_GetWindowSurface(window);//Get window surface
        }
    }

    /*------------------------------------------*/
    //Load images
    tile1 = SDL_LoadBMP("../../img/tile.bmp");
    tile2 = SDL_LoadBMP("../../img/tile2.bmp");
    if (tile1 == NULL || tile2 == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "../../img/tile2.bmp", SDL_GetError());
        goto Quit;
    }

    //Create textures with the BMP files
    case1 = SDL_CreateTextureFromSurface(renderer, tile1);
    SDL_FreeSurface(tile1);
    case2 = SDL_CreateTextureFromSurface(renderer, tile2);
    SDL_FreeSurface(tile2);
    if (case1 == NULL || case2 == NULL)
    {
        printf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    //Stock the textures into the stock grid
    stock[0] = case1;
    stock[1] = case2;

    SDL_Rect rectangle;
    rectangle.x = (WINDOW_WIDTH / 2) - (WINDOW_HEIGHT / 10) * 5;
    rectangle.y = 0;
    rectangle.w = (WINDOW_HEIGHT / 10);
    rectangle.h = (WINDOW_HEIGHT / 10);

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
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    ligne = event.button.y / (WINDOW_HEIGHT / 10);
                    colonne = (event.button.x - 80) / (WINDOW_HEIGHT / 10); 
                    printf("Clic en %dx/%dy\n", ligne, colonne);
                    if (!((ligne >= 0 && colonne >= 0) && (ligne < 10 && colonne < 10))){
                        continue;
                    }
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        printf("Clic gauche\n");
                        if (JEU[ligne][colonne] != stock[2]) {
                            reveal(JEU, MINE, ligne, colonne, victoire);
                        }
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        printf("Clic droit\n"); 
                        if (JEU[ligne][colonne] == stock[2])
                        {
                            if (JEU[ligne - 1][colonne] == stock[0] || (y != 0 && JEU[ligne][colonne - 1] == stock[0])) {
                                JEU[ligne][colonne] = stock[1];
                            }
                            else {
                                JEU[ligne][colonne] = stock[0];
                            }
                        }
                        if (JEU[ligne][colonne] == stock[0] || JEU[ligne][colonne] == stock[1])
                        {
                            JEU[ligne][colonne] = stock[2];
                        }
                    }
                    break;
                    
                case SDL_QUIT:
                    program_lanched = SDL_FALSE;
                    break;

                default :
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
            rectangle.x = ((WINDOW_WIDTH / 2) - (WINDOW_HEIGHT / 10) * 5) + (WINDOW_HEIGHT / 10) * x;
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
    if (NULL != case1)
        SDL_DestroyTexture(case1);
    if (NULL != case2)
        SDL_DestroyTexture(case2);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
    return statut;
}

void random_mine(int MINE[10][10], int x, int y, int ligne, int colonne) {//fonction de placement aléatoire d'un nombre de mine définis
    srand(time(NULL));
    int m;
    int nbMine = 10;//nombre de mine à placé sur la grille MINE
    for (m = 0; m < nbMine; m++) {
        x = rand() % 10;
        y = rand() % 10;
        if (MINE[x][y] == 0)//On vérifie que la case est libre
        {
            MINE[x][y] = 1;//on place un 1 pour indiquer qu'il y a une mine
        }
        else {
            nbMine++;
        }
    }
}

int checkMine(char JEU[10][10], int MINE[10][10], int x, int y) {//Calcul du nb de mine dans un rayon de 3x3
    if (x == 0 && y == 0) {
        return MINE[x][y + 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
    }
    else if (x == 0 && y == 9) {
        return MINE[x][y - 1] + MINE[x + 1][y + 1] + MINE[x][y + 1];
    }
    else if (x == 9 && y == 0) {
        return MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y + 1];
    }
    else if (x == 9 && y == 9) {
        return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x][y - 1];
    }
    else if (x == 0 && y > 0) {
        return MINE[x][y - 1] + MINE[x][y + 1] + MINE[x + 1][y - 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
    }
    else if (x > 0 && y == 0) {
        return MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y + 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
    }
    else if (x == 9 && y > 0) {
        return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y - 1] + MINE[x][y + 1];
    }
    else if (y == 9 && x > 0) {
        return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x][y - 1] + MINE[x + 1][y - 1] + MINE[x + 1][y];
    }
    else if ((x > 0 && y > 0) && (x < 9 && y < 9)) {
        return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y - 1] + MINE[x][y + 1] + MINE[x + 1][y - 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
    }
}

void reveal(char JEU[10][10], int MINE[10][10], int x, int y, int victoire) {
    int nbMine = checkMine(JEU, MINE, x, y);
    char mine = '0' + nbMine;
    //si x et y ne dépassent pas les bords
    if (!((x >= 0 && y >= 0) && (x < 10 && y < 10)))
        return;

    if (JEU[x][y] != '-')
        return;

    JEU[x][y] = mine;
    victoire -= 1;

    if (nbMine != 0)
        return;

    JEU[x][y] = mine;

    reveal(JEU, MINE, x - 1, y - 1, victoire);//haut gauche
    reveal(JEU, MINE, x - 1, y, victoire);//haut
    reveal(JEU, MINE, x - 1, y + 1, victoire);//haut droite
    reveal(JEU, MINE, x, y - 1, victoire);//gauche
    reveal(JEU, MINE, x, y + 1, victoire);//droite
    reveal(JEU, MINE, x + 1, y - 1, victoire);//bas gauche
    reveal(JEU, MINE, x + 1, y, victoire);//bas
    reveal(JEU, MINE, x + 1, y + 1, victoire);//bas droite

}