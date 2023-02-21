#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int i, j, b;//i les lignes, j les colonnes

void random_bomb()
{
    srand(time(NULL));
    for (b = 0; b < 10; b++) {
        int previ = rand() % 10;
        int prevj = rand() % 10;
        JEU[previ][prevj] = 'x';
        //printf("x=%d et y=%d \n", previ, prevj);
    }
}

int main()
{
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
            JEU[i][j] = '*';
            random_bomb();
            printf("%c  ", JEU[i][j]);
        }
        printf("\n");
    }

    return 0;
}
