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
    int nbLigne = 4, nbColonne = 4;
    int i, j, k;

    char **matrice;
    char **matrice_tmp;

    //matrice = allouerMemoireMemoire(nbLigne,nbColonne);
    //matrice = (char **) malloc(nbLigne * sizeof(char *));
    //matrice = (char **) calloc(4, sizeof(char *));

    //matrice_tmp = allouerMemoireMemoire(nbLigne,nbColonne);
    //matrice_tmp = (char **) malloc(nbLigne * sizeof(char *));

    /*for(i=0; i<nbLigne; i++)
    {
        matrice[i] = (char*) malloc(nbColonne * sizeof(char));
        matrice_tmp[i] = (char*) malloc(nbColonne * sizeof(char));
        //matrice[i] = (char*) calloc(4,sizeof(char));
    }*/

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

    matrice = initMatriceDeTest();
    matrice_tmp = initMatriceDeTest();

    /*

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

    */
    
    // Affichage matrice

    printf(" --- Affichage matrice");
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

    char **regles;
    int nbConditions = 3,nbCaracteres = 11;

    regles = allouerMemoireMemoire(nbConditions,nbCaracteres);
    /*
    regles = (char **) malloc(nbConditions * sizeof(char *));

    for(i = 0; i < nbConditions; i++){
        regles[i] = (char *) malloc(nbCaracteres * sizeof(char));
    }
    */

    // Initialisation des regles
    regles[0] = "fdsfsdf";

    
/*    printf("Condition 1 : '%s'\n",regles[0]);
    printf("Condition 1 - 2 : '%c'\n",regles[0][1]);*/


    regles[0] = "X-1O1O";  
    regles[1] = "0=8X1X";
    regles[2] = "A-1X1&-1O1X";

    // Traitement
    char *regleATest = regles[2];

    char **conditions = getConditions(regleATest);
    char *opLogique = getOperateursLogique(regleATest);
    char target = getTarget(regleATest);
    char res = getResult(regleATest);

    printf("Conditions : %s\n",conditions[0]);
    printf("Op logique : %s\n",opLogique);
    printf("Target : %c\n",target);
    printf("Res : %c\n",res);



    int *cpt;
    int nb_condi;

    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");

    for(i = 0;i< nbLigne;i++){
        for(j=0;j<nbColonne;j++){
            if(matrice[i][j] == regles[2][0]){
            	nb_condi = (int) (strlen(regles[2])/5);
            	cpt = (int*) malloc(nb_condi * sizeof(int));

            	for(k = 0; k<nb_condi; k++)
                {
                	cpt[k]= comptage(matrice,
	                            regles[2][3+k*5],
	                            i, j,nbLigne,nbColonne,
	                            atoi(&regles[2][4+k*5]));

	                // printf("---------------\n");
                	printf("%d\n",cpt[k] );
                	if(regles[2][1+k*5] == '-' && cpt[k] >= atoi(&regles[2][2+k*5]))
	              	{
	                	 printf("rentré\n");
	                	matrice_tmp[i][j]=regles[0][5+k*5];
	                }
	                else if(regles[2][1+k*5] == '+' && cpt[k] <= atoi(&regles[2][2+k*5]))
	                {
	                	printf("+\n");
	                	matrice_tmp[i][j]=regles[2][5+k*5];
	                }
	                else if(regles[2][1+k*5] == '0' && cpt[k] == 0 )
	                {
	                	printf("0\n");
	                	matrice_tmp[i][j]=regles[2][5+k*5];
	                }
	                else if(regles[2][1+k*5] == '=' && cpt[k] == atoi(&regles[2][2+k*5]))
	                {
	                	printf("=\n");
	                	matrice_tmp[i][j]=regles[2][5+k*5];
	                }
                }
            }
        }
    }
    //matrice = matrice_tmp;
    matrice = copierMatrice(matrice_tmp,nbLigne,nbColonne);

    for(i = 0;i< nbLigne;i++){
        for(j=0;j<nbColonne;j++){
        	printf("%c",matrice[i][j]);
        }
        printf("\n");
    }

    printf("\n#-----------------------#\n");
    printf("#    Fin traitement     #\n");
    printf("#-----------------------#\n\n");

/*    printf("Distance %d\n",atoi(&regles[0][4]));

    printf("Comptage = %d\n",cpt);*/

    // Désallocation de la mémoire

    desallouerMemoireMatrice(matrice,nbLigne);
    desallouerMemoireMatrice(matrice_tmp,nbLigne);

    /*
    for(i=0; i<4; i++)
    {
        free(matrice[i]);
        //free(matrice_tmp[i]);
    }

    free(matrice);
    //free(matrice_tmp);
    */

    return 0;
}
