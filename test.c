#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int x, y;//x les lignes, y les colonnes
char MINE[10][10];//la grille avec les mines
int nbMine;//le nombre de mine
int premier = 0;

void init()//fonction d'initialisation des grilles
{
    for (x = 0; x < 10; x++)
    {
        for (y = 0; y < 10; y++)
        {
            JEU[x][y] = '-';//affiche la grille de jeu avec des '-'
            MINE[x][y] = '0';//définis la grille de mine avec des '0'
        }
    }
}

void random_mine()//fonction de placement aléatoire d'un nombre de mine définis
{
    srand(time(NULL));
    int m;
    nbMine = 20;//nombre de mine à placé sur la grille MINE
    for (m = 0; m < nbMine; m++) {
        x = rand() % 10;
        y = rand() % 10;
        if (MINE[x][y] == '0')//On vérifie que la case est libre
        {
            MINE[x][y] = 'X';//on place un X pour indiquer qu'il y a une mine
        }
        else {
            nbMine++;
        }
    }
}

void afficherJeu() {
    printf("\n\n   | 1  2  3  4  5  6  7  8  9  10\n");
    printf("---|------------------------------\n");
    for (x = 0; x < 10; x++)
    {
        if (x < 9)
            printf(" %d | ", x + 1);
        else
            printf("%d | ", x + 1);
        for (y = 0; y < 10; y++)
        {
            printf("%c  ", JEU[x][y]);
        }
        printf("\n");
    }
}

void afficherMine() {
    printf("\n\n   | 1  2  3  4  5  6  7  8  9  10\n");
    printf("---|------------------------------\n");
    for (x = 0; x < 10; x++)
    {
        if (x < 9)
            printf(" %d | ", x + 1);
        else
            printf("%d | ", x + 1);
        for (y = 0; y < 10; y++)
        {
            printf("%c  ", MINE[x][y]);
        }
        printf("\n");
    }
}

int checkMine() {
    return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y - 1] + MINE[x][y + 1] + MINE[x + 1][y - 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
}

void play() {
    int ligne;
    int colonne;
    while (premier == 0) {
        printf("\nEntrez votre premiere case a jouer");
        printf("\nla ligne : "); scanf_s("%d", &ligne);
        printf("et la colonne : "); scanf_s("%d", &colonne);
        printf("\nvous avez joue la case (%d,%d)", ligne, colonne);
        ligne -= 1;
        colonne -= 1;
        if (JEU[x][y] <= JEU[ligne][colonne]) {
            JEU[ligne][colonne] = '0';
            premier++;
        }
        else {
            printf("\nERREUR");
            break;
        }
    }
}

int main()
{
    printf("\n *****    ******   **       **   *****   **    *   ******   *     *   ******  ");
    printf("\n *    *   *        * *     * *     *     * *   *   *        *     *   *     * ");
    printf("\n *    *   *****    *  *   *  *     *     *  *  *   *****    *     *   ******* ");
    printf("\n *    *   *        *   * *   *     *     *   * *   *        *     *   *    *  ");
    printf("\n *****    ******   *    *    *   *****   *    **   ******    *****    *     * ");

    init();//intialisation des grilles de jeu
    afficherJeu();
    play();
    afficherJeu();
    random_mine();
    checkMine();
    afficherMine();


    return 0;
}
