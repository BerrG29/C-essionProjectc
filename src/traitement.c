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
#include "client.h"
#include "dialPostTrait.h"

int main(int argc, char *argv[])
{
    int nbLigne = 4, nbColonne = 4;
    //int i, j, k, l;

    // Variables interraction utilisateur post traitement
    int bool_visualisation = 0;
    int bool_fin = 0;
    int index_iteration = 0;
    int nb_total_iterations = 0;
    int nb_iteration = 0;
    nb_total_iterations = 10;

    char **matrice;
    char **matrice_tmp;

    int **matriceForRules;

    // TRAITEMENT 

    // Écriture 

    matrice = initMatriceDeTest(nbLigne,nbColonne);
    matrice_tmp = initMatriceDeTest(nbLigne,nbColonne);
    matriceForRules = initMatriceRegles(nbLigne,nbColonne);

    // Fin écriture

    // Établissement règles

    int nbRegles = 0;

    char **regles;
    

    //printRes(regles);

    // Initialisation des regles

    printf("\n#-----------------------#\n");
    printf("#   Récupération règles #\n");
    printf("#-----------------------#\n\n");


    regles = rules(&nbRegles,&nb_iteration);
    printf("Nombre de regles %d\n",nbRegles);
    for(int i = 0; i < nbRegles ; i ++){
        printf("Regle %d = ",i);
        for(int j = 0; j < strlen(regles[i]); j++){
            printf("%c",regles[i][j]);
        }
        printf("\n");
    }

/*    printf("Condition 1 : '%s'\n",regles[0]);
    printf("Condition 1 - 2 : '%c'\n",regles[0][1]);*/


   /* int nbConditions = 3,nbCaracteres = 11;
    regles = allouerMemoireMatrice(nbConditions,nbCaracteres);
    regles[0] = "X-1O1O";  
    regles[1] = "O=8X1X";
    regles[2] = "A-1X1&-1O1X";*/

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

    //char *adr_server_odd = "148.60.220.134:5000/testReseau";
    //char *adr_server_pair = "148.60.220.134:5001/testReseau";

    char *adr_server_odd = "localhost:5000/simulation";
    char *adr_server_pair = "localhost:5001/simulation";
    //send_matrix(nbLigne, nbColonne, matrice, adr_server_odd, adr_server_pair);
    int compteur_cycle = 0;
    int cyclic = 1000;
    while(bool_fin!=1)
    {
        if(bool_visualisation==0)
        {
        	for(int f=0;f<nb_iteration;f++)
        	{

        		iteration(matrice,matrice_tmp,matriceForRules,nbLigne,nbColonne,regles,nbRegles);

        		//TODO : Desallouer la mémoire de la matrice avant de copier les valeurs de la matrice temp.
        		desallouerMemoireMatrice(matrice,nbLigne);
        		matrice = copierMatrice(matrice_tmp,nbLigne,nbColonne);
                // printf("Display adresse matrice : %p\n",matrice);
                // printf("Display adresse matrice temp : %p\n",matrice_tmp);

               // int cyclic = send_matrix(nbLigne, nbColonne, matrice, adr_server_odd, adr_server_pair);
                /*    if(cyclic==0)
                {
                    compteur_cycle++;
                }*/

                /*   printf("cyclic %d\n", cyclic);
                // TODO ici network

        		printf("\nTemps %d\n\n",f);*/
                reinitMatriceReglesAZero(matriceForRules,nbLigne,nbColonne);

        	}
            printf("Affichage matrice de l'itération %d\n",nb_iteration );
            for(int i = 0;i< nbLigne;i++)
            {
                for(int j=0;j<nbColonne;j++){
                    printf("%c",matrice[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
        else if(bool_visualisation == 1)
        {
            //TODO affichage matrice de l'itération index_iteration
            /*printf("affichage matrice de l'itération %d\n"index_iteration);*/
        }
        dialogue(&bool_visualisation,&index_iteration,&nb_iteration,&nb_total_iterations,&bool_fin);
    }

    printf("\n#-----------------------#\n");
	printf("#    Fin traitement     #\n");
    printf("#-----------------------#\n\n");

    // Désallocation de la mémoire

    desallouerMemoireMatrice(regles,nbRegles);

    desallouerMemoireMatrice(matrice,nbLigne);
    desallouerMemoireMatrice(matrice_tmp,nbLigne);
    // TODO : Désallouer la mémoire de la matrice for rules
    desallouerMemoireRegles(matriceForRules,nbRegles);

    return 0;
}