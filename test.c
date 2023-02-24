#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int x, y;//x les lignes, y les colonnes
int MINE[10][10];//la grille avec les mines
int nbMine;//le nombre de mine
int premier = 0;
int ligne;
int colonne;

void init()//fonction d'initialisation des grilles
{
    for (x = 0; x < 10; x++)
    {
        for (y = 0; y < 10; y++)
        {
            JEU[x][y] = '-';//affiche la grille de jeu avec des '-'
            MINE[x][y] = 0;//définis la grille de mine avec des 0
        }
    }
}

void random_mine()//fonction de placement aléatoire d'un nombre de mine définis
{
    srand(time(NULL));
    int m;
    nbMine = 10;//nombre de mine à placé sur la grille MINE
    for (m = 0; m < nbMine; m++) {
        x = rand() % 10;
        y = rand() % 10;
        if (MINE[x][y] == 0 || MINE[x][y] != MINE[ligne][colonne])//On vérifie que la case est libre
        {
            MINE[x][y] = 1;//on place un 1 pour indiquer qu'il y a une mine
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
            printf("%d  ", MINE[x][y]);
        }
        printf("\n");
    }
}

void play() {
    while (premier == 0) {
        printf("\nEntrez votre premiere case a jouer");
        printf("\nla ligne : "); scanf_s("%d", &ligne);
        printf("et la colonne : "); scanf_s("%d", &colonne);
        printf("\nvous avez joue la case (%d,%d)", ligne, colonne);
        ligne -= 1;
        colonne -= 1;
        if (JEU[x][y] <= JEU[ligne][colonne]) {
            JEU[ligne][colonne] = '*';
            premier++;
        }
        else {
            printf("\nERREUR");
            break;
        }
    }
}

int checkMine(int x, int y) {
    return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y - 1] + MINE[x][y + 1] + MINE[x + 1][y - 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
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
    random_mine();
    afficherJeu();
    printf("\n\nIl y a %d mines autour de ta case", checkMine(ligne, colonne));
    afficherMine();


    return 0;
}
