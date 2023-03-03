#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int x, y;//x les lignes, y les colonnes
int MINE[10][10];//la grille avec les mines
int ligne;
int colonne;
int maxDrapeau = 10;
int drapeau = 0;
int choix;
int victoire = 0;

void reveal(char JEU[10][10], int MINE[10][10], int x, int y);

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
    //retire la safe zone
    MINE[ligne][colonne] = 0;//case selec
    if (MINE[ligne - 1][colonne - 1] == 2 && (ligne != 0) && (colonne != 0)) {
        MINE[ligne - 1][colonne - 1] = 0;//haut gauche
    }
    if (MINE[ligne - 1][colonne] == 2 && (ligne != 0)) {
        MINE[ligne - 1][colonne] = 0;//haut
    }
    if (MINE[ligne - 1][colonne + 1] == 2 && (ligne != 0) && (colonne != 9)) {
        MINE[ligne - 1][colonne + 1] = 0;//haut droite
    }
    if (MINE[ligne][colonne - 1] == 2 && (colonne != 0)) {
        MINE[ligne][colonne - 1] = 0;//gauche
    }
    if (MINE[ligne][colonne + 1] == 2 && (colonne != 9)) {
        MINE[ligne][colonne + 1] = 0;//droite
    }
    if ((MINE[ligne + 1][colonne - 1] == 2) && (ligne != 9) && (colonne != 0)) {
        MINE[ligne + 1][colonne - 1] = 0;//bas gauche
    }
    if (MINE[ligne + 1][colonne] == 2 && (ligne != 9)) {
        MINE[ligne + 1][colonne] = 0;//bas
    }
    if (MINE[ligne + 1][colonne + 1] == 2 && (ligne != 9) && (colonne != 9)) {
        MINE[ligne + 1][colonne + 1] = 0;//bas droite
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
            //JEU[ligne][colonne] = '0';
            /*safe zone temporaire*/
            MINE[ligne][colonne] = 2;//case selec
            if (MINE[ligne - 1][colonne - 1] == 0 && (ligne != 0) && (colonne != 0)) {
                MINE[ligne - 1][colonne - 1] = 2;//haut gauche
            }
            if (MINE[ligne - 1][colonne] == 0 && (ligne != 0)) {
                MINE[ligne - 1][colonne] = 2;//haut
            }
            if (MINE[ligne - 1][colonne + 1] == 0 && (ligne != 0) && (colonne != 9)) {
                MINE[ligne - 1][colonne + 1] = 2;//haut droite
            }
            if (MINE[ligne][colonne - 1] == 0 && (colonne != 0)) {
                MINE[ligne][colonne - 1] = 2;//gauche
            }
            if (MINE[ligne][colonne + 1] == 0 && (colonne != 9)) {
                MINE[ligne][colonne + 1] = 2;//droite
            }
            if ((MINE[ligne + 1][colonne - 1] == 0) && (ligne != 9) && (colonne != 0)) {
                MINE[ligne + 1][colonne - 1] = 2;//bas gauche
            }
            if (MINE[ligne + 1][colonne] == 0 && (ligne != 9)) {
                MINE[ligne + 1][colonne] = 2;//bas
            }
            if (MINE[ligne + 1][colonne + 1] == 0 && (ligne != 9) && (colonne != 9)) {
                MINE[ligne + 1][colonne + 1] = 2;//bas droite
            }
            joue++;
        }
        else {
            printf("\nErreur de placement, la case (%d,%d) n'existe pas", ligne + 1, colonne + 1);
        }
    }
    random_mine();
    reveal(JEU, MINE, ligne, colonne);
}

int checkMine(int x, int y) {//Calcul du nb de mine dans un rayon de 3x3
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

void play() {
    int joue = 0;
    int imine;
    char mine;
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
                if (JEU[ligne][colonne] == '-') {
                    reveal(JEU, MINE, ligne, colonne);
                }
                else if (JEU[ligne][colonne] != '-') {
                    printf("\nCette case est deja joue ou marque");
                }
                joue++;
            }
            else if (choix == 2) {
                if (JEU[ligne][colonne] == '-') {
                    JEU[ligne][colonne] = '$';
                    maxDrapeau -= 1;
                    if ((MINE[ligne][colonne] == 1) == (JEU[ligne][colonne] == '$')) {
                        drapeau++;
                    }
                }
                else if (JEU[ligne][colonne] == '$') {
                    if ((MINE[ligne][colonne] == 1) == (JEU[ligne][colonne] == '$')) {
                        drapeau -= 1;
                    }
                    maxDrapeau++;
                    JEU[ligne][colonne] = '-';
                }
                else {
                    printf("\nCette case est deja joue, vous ne pouvez pas la marquer");
                }
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
                    if (JEU[ligne][colonne] == '-') {
                        reveal(JEU, MINE, ligne, colonne);
                    }
                    else if (JEU[ligne][colonne] != '-') {
                        printf("\nCette case est deja joue ou marque");
                    }
                    joue++;
                }
                else if (choix == 2) {
                    if (JEU[ligne][colonne] == '-') {
                        JEU[ligne][colonne] = '$';
                        maxDrapeau -= 1;
                        if ((MINE[ligne][colonne] == 1) == (JEU[ligne][colonne] == '$')) {
                            drapeau++;
                        }
                    }
                    else if (JEU[ligne][colonne] == '$') {
                        if ((MINE[ligne][colonne] == 1) == (JEU[ligne][colonne] == '$')) {
                            drapeau -= 1;
                        }
                        maxDrapeau++;
                        JEU[ligne][colonne] = '-';
                    }
                    else {
                        printf("\nCette case est deja joue, vous ne pouvez pas la marquer");
                    }
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

void reveal(char JEU[10][10], int MINE[10][10], int x, int y) {
    int nbMine = checkMine(x, y);
    char mine = '0' + nbMine;
    //si x et y ne dépassent pas les bords
    if (!((x >= 0 && y >= 0) && (x < 10 && y < 10)))
        return;

    if (JEU[x][y] != '-')
        return;

    JEU[x][y] = mine;
    victoire++;

    if (nbMine != 0)
        return;

    JEU[x][y] = mine;

    reveal(JEU, MINE, x - 1, y - 1);//haut gauche
    reveal(JEU, MINE, x - 1, y);//haut
    reveal(JEU, MINE, x - 1, y + 1);//haut droite
    reveal(JEU, MINE, x, y - 1);//gauche
    reveal(JEU, MINE, x, y + 1);//droite
    reveal(JEU, MINE, x + 1, y - 1);//bas gauche
    reveal(JEU, MINE, x + 1, y);//bas
    reveal(JEU, MINE, x + 1, y + 1);//bas droite

}



int main()
{

    printf("\n -----    ------   --     --   -----   --    -   ------   -    -   -----  ");
    printf("\n |    |   |        | |   | |     |     | |   |   |        |    |   |    | ");
    printf("\n |    |   -----    | |   | |     |     |  |  |   -----    |    |   |----  ");
    printf("\n |    |   |        |  | |  |     |     |   | |   |        |    |   |    | ");
    printf("\n -----    ------   -   -   -   -----   -    --   ------    ----    -    - ");

    int fin = 0;
    int okay = 9;
    init();//intialisation des grilles de jeu
    afficherJeu();
    firstPlay();//Premier tour du joueur
    //random_mine();//place les mine après le premier coup du joueur
    //reveal(JEU, MINE, ligne, colonne);
    afficherJeu();
    afficherMine();//affiche la grille des mines pour le debug
    printf("\ntu est a %d cases de la victoire", victoire);
    int imine = checkMine(x, y);
    char mine = '0' + imine;
    while (fin == 0) {
        play();
        afficherJeu();
        printf("\ntu est a %d cases de la victoire", victoire);
        if (MINE[ligne][colonne] == 1 && JEU[ligne][colonne] != '$' && choix != 2) {
            printf("\n\nPERDU, il y avait une mine a cet endroit, peut-etre la prochaine fois");
            fin++;
        }
        else if (victoire == 90 || drapeau == 10) {
            printf("\n\nBRAVO !!!");
            fin++;
        }
        afficherMine();//affiche la grille des mines pour le debug
    }

    printf("\n  ----     ----    --     --   ------       ----    -    -   ------   -----  ");
    printf("\n |        |    |   | |   | |   |           |    |   |    |   |        |    | ");
    printf("\n |  --    |----|   | |   | |   -----       |    |   |    |   -----    |----  ");
    printf("\n |    |   |    |   |  | |  |   |           |    |    |  |    |        |    | ");
    printf("\n  ----    -    -   -   -   -   ------       ----      --     ------   -    - \n");

    return 0;
}