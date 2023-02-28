#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int x, y;//x les lignes, y les colonnes
int MINE[10][10];//la grille avec les mines
//int nbMine;//le nombre de mine
int ligne;
int colonne;

void init() { //fonction d'initialisation des grilles
    for (x = 0; x < 10; x++)
    {
        for (y = 0; y < 10; y++)
        {
            JEU[x][y] = '-';//affiche la grille de jeu avec des '-'
            MINE[x][y] = 0;//définis la grille de mine avec des 0
        }
    }
}

void random_mine() {//fonction de placement aléatoire d'un nombre de mine définis
    srand(time(NULL));
    int m;
    int nbMine = 10;//nombre de mine à placé sur la grille MINE
    for (m = 0; m < nbMine; m++) {
        x = rand() % nbMine;
        y = rand() % nbMine;
        if ((MINE[x][y] == 0) || (MINE[x][y] != MINE[ligne][colonne]) || (MINE[x][y] != 2))//On vérifie que la case est libre
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

void firstPlay() {
    int joue = 0;
    while (joue == 0) {
        printf("\nEntrez votre premiere case a jouer");
        printf("\nla ligne : "); scanf_s("%d", &ligne);
        printf("et la colonne : "); scanf_s("%d", &colonne);
        printf("\nvous avez joue la case (%d,%d)", ligne, colonne);
        ligne -= 1;
        colonne -= 1;
        if (JEU[ligne][colonne] >= JEU[x][y] && JEU[colonne][ligne] >= JEU[y][x]) {
            JEU[ligne][colonne] = '0';
            //safe zone
            MINE[ligne][colonne] = 2;//case selec
            if (MINE[ligne - 1][colonne - 1] == 0 && (ligne != 0) && (colonne != 0)) {//finito
                MINE[ligne - 1][colonne - 1] = 2;//haut gauche
            }
            if (MINE[ligne - 1][colonne] == 0 && (ligne != 0)) {//finito
                MINE[ligne - 1][colonne] = 2;//haut
            }
            if (MINE[ligne - 1][colonne + 1] == 0 && (ligne != 0) && (colonne != 9)) {//finito
                MINE[ligne - 1][colonne + 1] = 2;//haut droite
            }
            if (MINE[ligne][colonne - 1] == 0 && (colonne != 0)) {//finito
                MINE[ligne][colonne - 1] = 2;//gauche
            }
            if (MINE[ligne][colonne + 1] == 0 && (colonne != 9)) {//finito
                MINE[ligne][colonne + 1] = 2;//droite
            }
            if ((MINE[ligne + 1][colonne - 1] == 0) && (ligne != 9) && (colonne != 0)) {//finito
                MINE[ligne + 1][colonne - 1] = 2;//bas gauche
            }
            if (MINE[ligne + 1][colonne] == 0 && (ligne != 9)) {//finito
                MINE[ligne + 1][colonne] = 2;//bas
            }
            if (MINE[ligne + 1][colonne + 1] == 0 && (ligne != 9) && (colonne != 9)) {//finito
                MINE[ligne + 1][colonne + 1] = 2;//bas droite
            }
            joue++;
        }
        else {
            printf("\nErreur de placement, la case (%d,%d) n'existe pas", ligne + 1, colonne + 1);
        }
    }
}


int checkMine(int x, int y) {//Calcul du nb de mine dans un rayon de 3x3
    return MINE[x - 1][y - 1] + MINE[x - 1][y] + MINE[x - 1][y + 1] + MINE[x][y - 1] + MINE[x][y + 1] + MINE[x + 1][y - 1] + MINE[x + 1][y] + MINE[x + 1][y + 1];
}

void play() {
    int joue = 0;
    int choix;
    while (joue == 0) {
        printf("\nQuelle case veut tu jouer ?");
        printf("\nla ligne : "); scanf_s("%d", &ligne);
        printf("et la colonne : "); scanf_s("%d", &colonne);
        printf("\nvous avez selectionne la case (%d,%d)", ligne, colonne);
        printf("\nQue voulez vous faire ? 1 deminer ou 2 marquer ou 3 rejouer : "); scanf_s("%d", &choix);
        ligne -= 1;
        colonne -= 1;
        if (JEU[ligne][colonne] >= JEU[x][y] && JEU[colonne][ligne] >= JEU[y][x]) {
            if (choix == 1) {
                if (checkMine(ligne, colonne) == 0) {
                    JEU[ligne][colonne] = '0';//(char)checkMine
                }
                else if (checkMine(ligne, colonne) == 1) {
                    JEU[ligne][colonne] = '1';
                }
                else if (checkMine(ligne, colonne) == 2) {
                    JEU[ligne][colonne] = '2';
                }
                else if (checkMine(ligne, colonne) == 3) {
                    JEU[ligne][colonne] = '3';
                }
                else if (checkMine(ligne, colonne) == 4) {
                    JEU[ligne][colonne] = '4';
                }
                else if (checkMine(ligne, colonne) == 5) {
                    JEU[ligne][colonne] = '5';
                }
                else if (checkMine(ligne, colonne) == 6) {
                    JEU[ligne][colonne] = '6';
                }
                else if (checkMine(ligne, colonne) == 7) {
                    JEU[ligne][colonne] = '7';
                }
                else if (checkMine(ligne, colonne) == 8) {
                    JEU[ligne][colonne] = '8';
                }
                joue++;
            }
            else if (choix == 2) {
                JEU[ligne][colonne] = '$';
                joue++;
            }
            else if (choix == 3) {
                printf("Vous rejouer");
            }
            else {
                while (choix < 1 || choix>3) {
                    printf("\nLe choix n'est pas correct");
                    printf("\nQue voulez vous faire ? 1 deminer ou 2 marquer ou 3 rejouer : "); scanf_s("%d", &choix);
                }
                if (choix == 1) {
                    if (checkMine(ligne, colonne) == 0) {
                        JEU[ligne][colonne] = '0';
                    }
                    else if (checkMine(ligne, colonne) == 1) {
                        JEU[ligne][colonne] = '1';
                    }
                    else if (checkMine(ligne, colonne) == 2) {
                        JEU[ligne][colonne] = '2';
                    }
                    else if (checkMine(ligne, colonne) == 3) {
                        JEU[ligne][colonne] = '3';
                    }
                    else if (checkMine(ligne, colonne) == 4) {
                        JEU[ligne][colonne] = '4';
                    }
                    else if (checkMine(ligne, colonne) == 5) {
                        JEU[ligne][colonne] = '5';
                    }
                    else if (checkMine(ligne, colonne) == 6) {
                        JEU[ligne][colonne] = '6';
                    }
                    else if (checkMine(ligne, colonne) == 7) {
                        JEU[ligne][colonne] = '7';
                    }
                    else if (checkMine(ligne, colonne) == 8) {
                        JEU[ligne][colonne] = '8';
                    }
                    joue++;
                }
                else if (choix == 2) {
                    JEU[ligne][colonne] = '$';
                    joue++;
                }
                else if (choix == 3) {
                    printf("Vous rejouer");
                }
            }
        }
        else {
            printf("\nErreur de placement, la case (%d,%d) n existe pas", ligne + 1, colonne + 1);
        }
    }
}



int main()
{
    printf("\n -----    ------   --     --   -----   --    -   ------   -    -   -----  ");
    printf("\n |    |   |        | |   | |     |     | |   |   |        |    |   |    | ");
    printf("\n |    |   -----    | |   | |     |     |  |  |   -----    |    |   |----  ");
    printf("\n |    |   |        |  | |  |     |     |   | |   |        |    |   |    | ");
    printf("\n -----    ------   -   -   -   -----   -    --   ------    ----    -    - ");

    int fin = 0;
    init();//intialisation des grilles de jeu
    afficherJeu();
    firstPlay();//Premier tour du joueur
    random_mine();//place les mine après le premier coup du joueur
    afficherJeu();
    printf("\nIl y a %d mines autour de ta case", checkMine(ligne, colonne));//debug pour checkMine
    afficherMine();//affiche la grille des mines pour le debug
    while (fin == 0) {
        play();
        //repeter checkMine jusqu'à plus de 0
        afficherJeu();
        printf("\n\nIl y a %d mines autour de ta case", checkMine(ligne, colonne));//debug pour checkMine
        if (MINE[ligne][colonne] == 1 && JEU[ligne][colonne] != '$') {
            printf("\n\nPERDU, il y avait une mine a cet endroit, peut-etre la prochaine fois");
            fin++;
        }
        /*else if (true) {
            printf("\n\nBRAVO !!!");
            fin++;
        }*/
        afficherMine();//affiche la grille des mines pour le debug
    }

    printf("\n  ----     ----    --     --   ------       ----    -    -   ------   -----  ");
    printf("\n |        |    |   | |   | |   |           |    |   |    |   |        |    | ");
    printf("\n |  --    |----|   | |   | |   -----       |    |   |    |   -----    |----  ");
    printf("\n |    |   |    |   |  | |  |   |           |    |    |  |    |        |    | ");
    printf("\n  ----    -    -   -   -   -   ------       ----      --     ------   -    - \n");

    return 0;
}