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

    // TRAITEMENT 

    // Écriture 

    matrice = initMatriceDeTest();
    matrice_tmp = initMatriceDeTest();

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

    regles = allouerMemoireMatrice(nbConditions,nbCaracteres);

    // Initialisation des regles
    regles[0] = "fdsfsdf";

    printf("\n#-----------------------#\n");
    printf("#   Récupération règles #\n");
    printf("#-----------------------#\n\n");

/*    printf("Condition 1 : '%s'\n",regles[0]);
    printf("Condition 1 - 2 : '%c'\n",regles[0][1]);*/

    regles[0] = "X-1O1O";  
    regles[1] = "0=8X1X";
    regles[2] = "A-1X1&-1O1X";

    printf("\n#-----------------------#\n");
    printf("#   Affichage différentes valeurs règles   #\n");
    printf("#-----------------------#\n\n");

    // Traitement
    char *regleATest = regles[2];

    char **conditions = getConditions(regleATest);
    char *opLogique = getOperateursLogiqueLiaison(regleATest);
    char target = getTarget(regleATest);
    char res = getResult(regleATest);

    // printf("Conditions : %s\n",conditions[0]);
    // printf("Conditions : %s\n",conditions[1]);
    // printf("Conditions : %s\n",conditions[2]);
    printf("Op logique : %s\n",opLogique);
    printf("Target : %c\n",target);
    printf("Res : %c\n",res);

    int *cpt;
    int nb_condi;

    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");

    for(int l = 0 ; l < strlen(regles) ; l++){
        printf("Regle[%d] = %s\n",l,regles[l]);
    }


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

    //desallouerMemoireMatrice(conditions,PARAMETRES_DANS_CONDITIONS);
    //desallouerMemoireMatrice(regles,nbConditions);

    //matrice = matrice_tmp;
    //TODO : Desallouer la mémoire de la matrice avant de copier les valeurs de la matrice temp.
    //desallouerMemoireMatrice(matrice,nbLigne);
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

    return 0;
}
