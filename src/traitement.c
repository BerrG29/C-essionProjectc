/**
 * 
 * Pour lancer le traitement, il suffit d'exécuter : 
 * gcc -Wall traitement.c -o a.out && ./a.out
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "lib.c"

int main(int argc, char *argv[])
{
    char **matrice;
    int nbLigne = 4, nbColonne = 4;
    matrice = (char **) malloc(nbLigne * sizeof(char *));
    //matrice = (char **) calloc(4, sizeof(char *));

    int i, j, k;
    for(i=0; i<nbLigne; i++)
    {
        matrice[i] = (char*) malloc(nbColonne * sizeof(char));
        //matrice[i] = (char*) calloc(4,sizeof(char));
    }

    char **matrice_tmp;
    matrice_tmp = (char **) malloc(nbLigne * sizeof(char *));
    //matrice = (char **) calloc(4, sizeof(char *));

    for(i=0; i<nbLigne; i++)
    {
        matrice_tmp[i] = (char*) malloc(nbColonne * sizeof(char));
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

    matrice_tmp[0][0] = 'X';
    matrice_tmp[0][1] = 'X';
    matrice_tmp[0][2] = 'X';
    matrice_tmp[0][3] = 'X';

    matrice_tmp[1][0] = 'X';
    matrice_tmp[1][1] = 'X';
    matrice_tmp[1][2] = 'O';
    matrice_tmp[1][3] = 'X';

    matrice_tmp[2][0] = 'X';
    matrice_tmp[2][1] = 'X';
    matrice_tmp[2][2] = 'X';
    matrice_tmp[2][3] = 'X';

    matrice_tmp[3][0] = 'X';
    matrice_tmp[3][1] = 'A';
    matrice_tmp[3][2] = 'X';
    matrice_tmp[3][3] = 'X';




    
    // Affichage matrice
    for(i=0; i<nbLigne; i++)
    {
        for(j=0; j<nbColonne; j++)
        {
            printf("%c",matrice_tmp[i][j]);
        }
        printf("\n");
    }
    // Fin écriture

    // Établissement règles

    char **conditions;
    int nbConditions = 3,nbCaracteres = 11;

    conditions = (char **) malloc(nbConditions * sizeof(char *));

    for(i = 0; i < nbConditions; i++){
        conditions[i] = (char *) malloc(nbCaracteres * sizeof(char));
    }


    // Initialisation des conditions
    conditions[0] = "fdsfsdf";

    
/*    printf("Condition 1 : '%s'\n",conditions[0]);
    printf("Condition 1 - 2 : '%c'\n",conditions[0][1]);*/


    conditions[0] = "X-1O1O";  
    conditions[1] = "0=8X1X";
    conditions[2] = "A-1X1-1O1X";

    // Traitement

    int *cpt;
    int nb_condi;
    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");




    for(i = 0;i< nbLigne;i++){
        for(j=0;j<nbColonne;j++){
            if(matrice[i][j] == conditions[2][0]){
            	nb_condi = (int) (strlen(conditions[2])/5);
            	cpt = (int*) malloc(nb_condi * sizeof(int));

            	for(k = 0; k<nb_condi; k++)
                {
                	

	                cpt[k]= comptage(matrice,
	                            conditions[2][3+k*5],
	                            i, j,nbLigne,nbColonne,
	                            atoi(&conditions[2][4+k*5]));

	                // printf("---------------\n");
                	printf("%d\n",cpt[k] );
                	if(conditions[2][1+k*5] == '-' && cpt[k] >= atoi(&conditions[2][2+k*5]))
	              	{
	                	 printf("rentré\n");
	                	matrice_tmp[i][j]=conditions[0][5+k*5];
	                }
	                else if(conditions[2][1+k*5] == '+' && cpt[k] <= atoi(&conditions[2][2+k*5]))
	                {
	                	printf("+\n");
	                	matrice_tmp[i][j]=conditions[2][5+k*5];
	                }
	                else if(conditions[2][1+k*5] == '0' && cpt[k] == 0 )
	                {
	                	printf("0\n");
	                	matrice_tmp[i][j]=conditions[2][5+k*5];
	                }
	                else if(conditions[2][1+k*5] == '=' && cpt[k] == atoi(&conditions[2][2+k*5]))
	                {
	                	printf("=\n");
	                	matrice_tmp[i][j]=conditions[2][5+k*5];
	                }
                }
            }
        }
    }
    matrice = matrice_tmp;

  for(i = 0;i< nbLigne;i++){
        for(j=0;j<nbColonne;j++){
        	printf("%c",matrice[i][j]);
        }
        printf("\n");
    }

/*    printf("Distance %d\n",atoi(&conditions[0][4]));

    printf("Comptage = %d\n",cpt);*/

    // Désallocation de la mémoire

    for(i=0; i<4; i++)
    {
        free(matrice[i]);
    }

    free(matrice);

    return 0;

}
