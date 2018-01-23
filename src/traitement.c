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

    regles = allouerMemoireMemoire(nbConditions,nbCaracteres);

    // Initialisation des regles
    regles[0] = "fdsfsdf";

    
/*    printf("Condition 1 : '%s'\n",regles[0]);
    printf("Condition 1 - 2 : '%c'\n",regles[0][1]);*/

    regles[0] = "X-1O1O";  
    regles[1] = "0=8X1X";
    regles[2] = "A-1X1&-1O1X";

    // Traitement
   /* char *regleATest = regles[2];*/

    // char **conditions = getConditions(regleATest);
 /*   char *opLogique = getOperateursLogique(regleATest);
    char target = getTarget(regleATest);
    char res = getResult(regleATest);*/

    /*printf("Conditions : %s\n",conditions[0]);
    printf("Op logique : %s\n",opLogique);
    printf("Target : %c\n",target);
    printf("Res : %c\n",res);*/

    int *cpt;
    int nb_condi;

    printf("\n#-----------------------#\n");
    printf("#   Début traitement    #\n");
    printf("#-----------------------#\n\n");

    char target;
    char **conditions;
    char resultat;
    char *operateur;

    int premiere_condi;
    int deuxieme_condi;

   

    for(i = 0;i< nbLigne;i++){

        for(j=0;j<nbColonne;j++){

        	target = getTarget(regles[0]);
        	conditions = getConditions(regles[0]);
        	resultat = getResult(regles[0]);
        	operateur = getOperateursLogique(regles[0]);
        	nb_condi = getNBConditions(regles[0]);

        	premiere_condi = 0;
  			deuxieme_condi = 0;

            if(matrice[i][j] == target){

            	
            	cpt = (int*) malloc(nb_condi * sizeof(int));

            	for(k = 0; k<nb_condi; k++)
                {

                	cpt[k]= comptage(matrice,regles[0][3+k*5], i, j,nbLigne,nbColonne,atoi(&regles[0][4+k*5]));

					/*printf(" k =  %d \n",k);
                	printf(" cpt %d \n",cpt[k]);*/

	                if(nb_condi == 1)
	                {
	                	if(regles[0][1] == '-' && cpt[0] >= atoi(&regles[0][2]))
		              	{
		           
		                	matrice_tmp[i][j]=regles[0][5];
		                }
		                else if(regles[0][1] == '+' && cpt[0] <= atoi(&regles[0][2]))
		                {
		                	
		                	matrice_tmp[i][j]=regles[0][5];
		                }
		                else if(regles[0][1] == '0' && cpt[0] == 0 )
		                {
		                	
		                	matrice_tmp[i][j]=regles[0][5];
		                }
		                else if(regles[0][1] == '=' && cpt[0] == atoi(&regles[0][2]))
		                {
		                	
		                	matrice_tmp[i][j]=regles[0][5];
		                }
	                }
	                else{

	                	/*
						Validation deuxième condition
						*/

	                	if(regles[0][1] == '-' && cpt[0] >= atoi(&regles[0][2]))
		              	{
		                	
		                	premiere_condi=1;
		                }
		                else if(regles[0][1] == '+' && cpt[0] <= atoi(&regles[0][2]))
		                {
		                	
		                	premiere_condi=1;
		                }
		                else if(regles[0][1] == '0' && cpt[0] == 0 )
		                {
		                	
		                	premiere_condi=1;
		                }
		                else if(regles[0][1] == '=' && cpt[0] == atoi(&regles[0][2]))
		                {
		                	
		                	premiere_condi=1;
		                }

						/*
						Validation deuxième condition
						*/

		                if(regles[0][6] == '-' && cpt[1] >= atoi(&regles[0][7]))
		              	{
		                	
		                	deuxieme_condi=1;
		                }
		                else if(regles[0][6] == '+' && cpt[1] <= atoi(&regles[0][7]))
		                {
		                	
		                	deuxieme_condi=1;
		                }
		                else if(regles[0][6] == '0' && cpt[1] == 0 )
		                {
		                	
		                	deuxieme_condi=1;
		                }
		                else if(regles[0][6] == '=' && cpt[1] == atoi(&regles[0][7]))
		                {
		                	
		                	deuxieme_condi=1;
		                }

		                /*
						test sur les conditions 
						*/

		                if(operateur == "&")
		                {
		                	if(premiere_condi == 1 && deuxieme_condi == 1)
		                	{
		                		matrice_tmp[i][j]=regles[0][10];
		                	}
		                }
		                else
		                {
		                	if(premiere_condi == 1 || deuxieme_condi == 1)
		                	{
		                		matrice_tmp[i][j]=regles[0][10];
		                	}
		                }

	                }
                }
            }
        }
    }
    //matrice = matrice_tmp;
    matrice = copierMatrice(matrice_tmp,nbLigne,nbColonne);

 

    printf("\n#-----------------------#\n");
    printf("#    Fin traitement     #\n");
    printf("#-----------------------#\n\n");


	printf("\n --- Affichage matrice sortie\n");

    for(i = 0;i< nbLigne;i++){
        for(j=0;j<nbColonne;j++){
        	printf("%c",matrice[i][j]);
        }
        printf("\n");
    }
/*    printf("Distance %d\n",atoi(&regles[0][4]));

    printf("Comptage = %d\n",cpt);*/

    // Désallocation de la mémoire

    desallouerMemoireMatrice(matrice,nbLigne);
    desallouerMemoireMatrice(matrice_tmp,nbLigne);

    return 0;
}
