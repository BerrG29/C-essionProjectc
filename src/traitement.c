/**
 * 
 * Pour lancer le traitement, il suffit d'exécuter : 
 * gcc -Wall traitement.c -o a.out && ./a.out
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lib.c"

int main(int argc, char *argv[])
{
    char **matrice;
    int nbLigne = 4, nbColonne = 4;
    matrice = (char **) malloc(nbLigne * sizeof(char *));
    //matrice = (char **) calloc(4, sizeof(char *));

    int i, j;
    for(i=0; i<nbLigne; i++)
    {
        matrice[i] = (char*) malloc(nbColonne * sizeof(char));
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

    // matrice[0] = "XXXX";
    // matrice[1] = "XX0X";
    // matrice[2] = "XXXX";
    // matrice[3] = "XAXX";

    matrice[0][0] = 'X';
    matrice[0][1] = 'X';
    matrice[0][2] = 'X';
    matrice[0][3] = 'X';

    matrice[1][0] = 'X';
    matrice[1][1] = 'X';
    matrice[1][2] = 'X';
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
    for(i=0; i<nbLigne; i++)
    {
        for(j=0; j<nbColonne; j++)
        {
            printf("%c",matrice[i][j]);
        }
        printf("\n");
    }

    // Fin écriture

    // Établissement règles

    char **conditions;
    int nbConditions = 3,nbCaracteres = 11;

    conditions = (char **) malloc(nbConditions * sizeof(char *));

    for(int i = 0; i < nbConditions; i++){
        conditions[i] = (char *) malloc(nbCaracteres * sizeof(char));
    }


    // Initialisation des conditions
    conditions[0] = "fdsfsdf";

    int len;
    printf("Condition 1 : '%s'\n",conditions[0]);
    printf("Condition 1 - 2 : '%c'\n",conditions[0][1]);


    conditions[0] = "X-1O1O";  
    conditions[1] = "0=8X1X";
    conditions[2] = "A-1X1-1O1X";

    len = strlen(conditions[0]);
    printf("Length 1 : '%d'\n",len);  

    // Traitement

    int cpt;

    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");

    for(i = 0;i< nbLigne;i++){
        for(j=0;j<nbColonne;j++){

            if(matrice[i][j] == conditions[0][0]){
                cpt= comptage(matrice,
                            conditions[0][0],
                            i, j,nbLigne,nbColonne,
                            atoi(&conditions[0][4]));
                printf("---------------\n");
            }
        }
    }



    printf("Distance %d\n",atoi(&conditions[0][4]));

    printf("Comptage = %d\n",cpt);

    // Désallocation de la mémoire

    for(i=0; i<4; i++)
    {
        free(matrice[i]);
    }

    free(matrice);

    return 0;

}

int testCaseAutour(char**matrice, int indexLig, int indexCol, int nbCaseAutour, int nbLig, int nbCol, char * condition){
    int i, j;

    int indexDebLig, indexDebCol, indexFinLig, indexFinCol;
    indexDebLig = index - nbCaseAutour;


    for(i = 0; i<nbLig; i++){
        for(j = 0; j<nbCol;j++){
            
        }
    }
}