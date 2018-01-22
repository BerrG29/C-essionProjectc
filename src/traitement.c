#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char **matrice;
    matrice = (char **) malloc(4 * sizeof(char *));
    //matrice = (char **) calloc(4, sizeof(char *));

    int i, j;
    for(i=0; i<4; i++)
    {
        matrice[i] = (char*) malloc(4 * sizeof(char));
        //matrice[i] = (char*) calloc(4,sizeof(char));
    }

    // TRAITEMENT 

    // Écriture 

    /*
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            //TODO: Depuis la matrice envoyé par l'utilisateur
            matrice[i][j] = 0;
        }
    }*/

    matrice[0][0] = 'X';
    matrice[0][1] = 'X';
    matrice[0][2] = 'X';
    matrice[0][3] = 'X';

    matrice[1][0] = 'X';
    matrice[1][1] = 'X';
    matrice[1][2] = 'O';
    matrice[1][3] = 'X';

    matrice[2][0] = 'X';
    matrice[2][1] = 'X';
    matrice[2][2] = 'X';
    matrice[2][3] = 'X';

    matrice[3][0] = 'X';
    matrice[3][1] = 'A';
    matrice[3][2] = 'X';
    matrice[3][3] = 'X';


    // Affichage matrice
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%c",matrice[i][j]);
        }
        printf("\n");
    }

    // Fin écriture

    // Établissement règles







    for(i=0; i<4; i++)
    {
        free(matrice[i]);
    }

    free(matrice);



    return 0;

}