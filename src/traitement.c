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
#include "rulesDef.c"

int main(int argc, char *argv[])
{
    int nbLigne = 4, nbColonne = 7;
    //int i, j, k, l;

    char **matrice;
    char **matrice_tmp;

    // TRAITEMENT 

    // Écriture 

    matrice = initMatriceDeTest();
    matrice_tmp = initMatriceDeTest();

    // Fin écriture

    // Établissement règles

    int nbRegles = 0;

    char **regles;
    

    //printRes(regles);

    // Initialisation des regles

    printf("\n#-----------------------#\n");
    printf("#   Récupération règles #\n");
    printf("#-----------------------#\n\n");

    regles = rules(&nbRegles);
    printf("Nombre de regles %d\n",nbRegles);
    for(int i = 0; i < nbRegles ; i ++){
        for(int j = 0; j < strlen(regles[i]); j++){
            printf("Regle %d = %s",i,regles[i]);
        }
        printf("\n");
    }

/*    printf("Condition 1 : '%s'\n",regles[0]);
    printf("Condition 1 - 2 : '%c'\n",regles[0][1]);*/

    // int nbConditions = 3,nbCaracteres = 11;
    // regles = allouerMemoireMatrice(nbConditions,nbCaracteres);
    // regles[0] = "X-1O1O";  
    // regles[1] = "0=8X1X";
    // regles[2] = "A-1X1&-1O1X";

	// regles[0] = "O-1/1A";  
    // regles[1] = "A05O2O";
    // regles[2] = "A+2A1$";

	// regles[0] = "X+2A2O";  
    // regles[1] = "O-3X1X";
    // regles[2] = "A=3X1&-2O2X";


    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");

	// Affichage matrice

    printf(" --- Affichage matrice  origine\n");
    for(int i=0; i<nbLigne; i++)
    {
        for(int j=0; j<nbColonne; j++)
        {
            printf("%c",matrice_tmp[i][j]);
        }
        printf("\n");
    }


    // for(int l = 0 ; l < strlen(regles) ; l++){
    //     printf("Regle[%d] = %s\n",l,regles[l]);
    // }
    // int premiere_condi;
    // int deuxieme_condi;

		// Lancement

	for(int f=0;f<10;f++)
	{
		iteration(matrice,matrice_tmp,nbLigne,nbColonne,regles,3);


		//matrice = matrice_tmp;
		//TODO : Desallouer la mémoire de la matrice avant de copier les valeurs de la matrice temp.
		//desallouerMemoireMatrice(matrice,nbLigne);
		matrice = copierMatrice(matrice_tmp,nbLigne,nbColonne);

        // TODO

		printf("\ntemps %d\n\n",f );

		for(int i = 0;i< nbLigne;i++){
			for(int j=0;j<nbColonne;j++){
				printf("%c",matrice[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
 

    printf("\n#-----------------------#\n");
	printf("#    Fin traitement     #\n");
    printf("#-----------------------#\n\n");

    // Désallocation de la mémoire

	//desallouerMemoireMatrice(conditions,PARAMETRES_DANS_CONDITIONS);
    //desallouerMemoireMatrice(regles,nbConditions);

    desallouerMemoireMatrice(matrice,nbLigne);
    desallouerMemoireMatrice(matrice_tmp,nbLigne);

    return 0;
}