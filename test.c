#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int i, j;//i les lignes, j les colonnes
char MINE[10][10];//la grille avec les mines
int nbMine;//le nombre de mine

void init()
{
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            JEU[i][j] = '-';//' 'implique case cachée
            MINE[i][j] = '0';
        }
    }
}

void random_mine()
{
    srand(time(NULL));
    int b;
    nbMine = 20;
    for (b = 0; b < nbMine; b++) {
        i = rand() % 10;
        j = rand() % 10;
        if (MINE[i][j] == '0')//On vérifie que la case est libre
        {
            MINE[i][j] = 'X';//on place un M pour indiquer qu'il y a une mine
        }
        else {
            nbMine++;
        }
    }
}

void afficherJeu() {
    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
    printf("---|------------------------------\n");
    for (i = 0; i < 10; i++)
    {
        if (i < 9)
            printf(" %d | ", i + 1);
        else
            printf("%d | ", i + 1);
        for (j = 0; j < 10; j++)
        {
            printf("%c  ", JEU[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    init();
    random_mine();
    afficherJeu();

    return 0;
}
