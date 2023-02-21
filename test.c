#include <iostream>

char JEU[10][10];//grille de jeu 
int i, j;//i les lignes, j les colonnes

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
            printf("%c  ", JEU[i][j]);
        }
        printf("\n");
    }
}