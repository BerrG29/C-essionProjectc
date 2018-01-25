#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

void dialogue(int *bool_visu, int *index_iteration, int *nb_iteration, int *nb_total, int *bool_fin, int *stable, int *periode){

	char ok = "";
	char term = "";
	int valid = 0;

	if(*stable==1)
	{
		printf("La matrice est stable\n");
	}

	if(*periode!=0){
		printf("la matrice est cyclique de periode %d\n", *periode);
	}
	printf("Voulez vous visualiser une itération particulière (O/N)?\n");
	scanf(" %c%c", &ok, &term);
	valid = 0;
	while(valid!=1){

		if(ok =='O' || ok =='N')
		{
			valid = 1;
		}
		else
		{
	 		printf("Ce caractère est interdit.\n\n");
	 		printf("Voulez vous visualiser une itération particulière (O/N)?\n");
			scanf("%c%c",&ok,&term);
		}
 	}
 	valid = 0;

 	if (ok == 'O')
 	{
		*bool_visu = 1;
		printf("Quelle itération voulez vous visualiser ? entier entre (0 et %d)\n",*nb_total);

		while(valid!=1){
			if(scanf("%d%c", index_iteration, &term) == 2 && *index_iteration > *nb_total)
			{
				valid = 1;
			}
			else
			{
		 	printf("Merci d'entrer un entier entre 0 et %d \n", *nb_total);
		 	scanf(" %c",&term);
			printf("Quelle itération voulez vous visualiser ? entier entre (0 et %d)\n",*nb_total);
			}
		}
 	}
 	else if (ok == 'N')
 	{
 		*bool_visu = 0;
		printf("Voulez-vous relancer des itérations (O/N)?\n");
		scanf("%c%c", &ok, &term);
		valid = 0;
		while(valid!=1)
		{

			if(ok =='O' || ok =='N')
			{
				valid = 1;
			}
			else
			{
		 		printf("Ce caractère est interdit.\n\n");
		 		printf("Voulez-vous relancer des itérations (O/N)?\n");
				scanf("%c%c",&ok,&term);
			}
 		}
 		valid = 0;
 		if (ok == 'O')
 		{
 			printf("Combien d'itération voulez-vous relancer ? (entrez 1 entier)\n");
 			while(valid!=1){
				if(scanf("%d%c", nb_iteration, &term) == 2 && nb_iteration > 0)
				{
					valid = 1;
				}
				else
				{
			 	printf("Merci d'entrer un entier \n");
			 	scanf(" %c",&term);
				printf("Combien d'itération voulez-vous relancer ? (entrez 1 entier)\n");
				}
			}
 		}
 		else
 		{
 			*bool_fin = 1;
 		}	
 	}
}