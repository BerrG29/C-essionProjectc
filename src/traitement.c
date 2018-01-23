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
    int nbLigne = 1, nbColonne = 6;
    int i, j, k, l;

    char **matrice;
    char **matrice_tmp;

    // TRAITEMENT 

    // Écriture 

    matrice = initMatriceDeTest2();
    matrice_tmp = initMatriceDeTest2();

    // Affichage matrice

    printf(" --- Affichage matrice  origine\n");
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

    //regles[0] = "X-1O1O";  
    //regles[1] = "0=8X1X";
    //regles[2] = "A-1X1&-1O1X";

	regles[0] = "O-1/1A";  
    regles[1] = "A05O2O";
    regles[2] = "A+2A1$";

    printf("\n#-----------------------#\n");
    printf("#   Affichage différentes valeurs règles   #\n");
    printf("#-----------------------#\n\n");

    // Traitement
    char *regleATest = regles[2];

    char **conditions = getConditions(regleATest);
    char *operateur = getOperateursLogiqueLiaison(regleATest);
    char target = getTarget(regleATest);
    char resultat = getResult(regleATest);

    // printf("Conditions : %s\n",conditions[0]);
    // printf("Conditions : %s\n",conditions[1]);
    // printf("Conditions : %s\n",conditions[2]);
    printf("Op logique : %s\n",operateur);
    printf("Target : %c\n",target);
    printf("Res : %c\n",resultat);


    int *cpt;
    int nb_condi;

    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");


    for(int l = 0 ; l < strlen(regles) ; l++){
        printf("Regle[%d] = %s\n",l,regles[l]);
    }
    int premiere_condi;
    int deuxieme_condi;

	void iteration()
	{
		for(l=2; l>=0;l--)
		{

			for(i = 0;i< nbLigne;i++)
			{

				for(j=0;j<nbColonne;j++)
				{

					target = getTarget(regles[l]);
					conditions = getConditions(regles[l]);
					resultat = getResult(regles[l]);
					operateur = getOperateursLogiqueLiaison(regles[l]);
					nb_condi = getNBConditions(regles[l]);

					premiere_condi = 0;
					deuxieme_condi = 0;

					if(matrice[i][j] == target)
					{
						cpt = (int*) malloc(nb_condi * sizeof(int));

						for(k = 0; k<nb_condi; k++)
						{
							cpt[k]= comptage(matrice,regles[l][3+k*5], i, j,nbLigne,nbColonne,atoi(&regles[l][4+k*5]));
						}

						/*printf(" k =  %d \n",k);
						printf(" cpt %d \n",cpt[k]);*/

						if(nb_condi == 1)
						{
							if(regles[l][1] == '-' && cpt[0] >= atoi(&regles[l][2]))
							{
					
								matrice_tmp[i][j]=regles[l][5];
							}
							else if(regles[l][1] == '+' && cpt[0] <= atoi(&regles[l][2]))
							{
								
								matrice_tmp[i][j]=regles[l][5];
							}
							else if(regles[l][1] == '0' && cpt[0] == 0 )
							{
								/*printf("rentré 0\n");
								printf("charactere a remplacer = %c",regles[l][5]);
								printf("normalement  = %c",regles[1][5]);*/
								matrice_tmp[i][j]=regles[l][5];
							}
							else if(regles[l][1] == '=' && cpt[0] == atoi(&regles[l][2]))
							{
								
								matrice_tmp[i][j]=regles[l][5];
							}
						}
						else{

							/*
							Validation deuxième condition
							*/

							if(regles[l][1] == '-' && cpt[0] >= atoi(&regles[l][2]))
							{
								
								premiere_condi=1;
							}
							else if(regles[l][1] == '+' && cpt[0] <= atoi(&regles[l][2]))
							{
								
								premiere_condi=1;
							}
							else if(regles[l][1] == '0' && cpt[0] == 0 )
							{
								
								premiere_condi=1;
							}
							else if(regles[l][1] == '=' && cpt[0] == atoi(&regles[l][2]))
							{
								
								premiere_condi=1;
							}

							/*
							Validation deuxième condition
							*/
							
							if(regles[l][6] == '-' && cpt[1] >= atoi(&regles[l][7]))
							{
								
								deuxieme_condi=1;
							}
							else if(regles[l][6] == '+' && cpt[1] <= atoi(&regles[l][7]))
							{
								
								deuxieme_condi=1;
							}
							else if(regles[l][6] == '0' && cpt[1] == 0 )
							{
								
								deuxieme_condi=1;
							}
							else if(regles[l][6] == '=' && cpt[1] == atoi(&regles[l][7]))
							{
								deuxieme_condi=1;
							}

							/*
							test sur les conditions 
							*/
							
							if(operateur[0] == '&')
							{
								
								if(premiere_condi == 1 && deuxieme_condi == 1)
								{
									
									matrice_tmp[i][j]=regles[l][10];
								}
							}
							else if(operateur[0] == '|')
							{
								if(premiere_condi == 1 || deuxieme_condi == 1)
								{
									
									matrice_tmp[i][j]=regles[l][10];
								}
							}

						}				
					}
				}
			}
		}
	}



	int f;

		// Lancement

	for(f=0;f<10;f++)
	{
		iteration();

		//matrice = matrice_tmp;
		//TODO : Desallouer la mémoire de la matrice avant de copier les valeurs de la matrice temp.
		//desallouerMemoireMatrice(matrice,nbLigne);
		matrice = copierMatrice(matrice_tmp,nbLigne,nbColonne);

		printf("\ntemps %d\n\n",f );

		for(i = 0;i< nbLigne;i++){
			for(j=0;j<nbColonne;j++){
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
