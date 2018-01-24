#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

void dialogue(int *bool_visu, int *index_iteration, int *nb_iteration, int *nb_total, int *bool_fin){

	char ok = "";
	char term = "";
	int valid = 0;

	/*if(*nb_cycles==*nb_total_iterations)
	{
		printf("Aucune stabilité\n" );
	}
	else{
		printf("La matrice devient stable à la %d itération \n",*nb_cycles);
	}*/
	printf("Voulez vous visualiser une itération particulière (O/N)?\n");
	scanf(" %c%c", &ok, &term);
	printf("ok = %c\n",ok );
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
			if(scanf("%d%c", index_iteration, &term) == 2 && index_iteration > *nb_total)
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


/*int main(int argc, char const *argv[])
{
	int bool_visualisation = 0;
	int bool_fin = 0;
	int index_iteration = 0;
	int nb_total_iterations = 0;
	int nb_iteration = 0;
	nb_total_iterations = 15;


	dialogue(&bool_visualisation,&index_iteration,&nb_iteration,&nb_total_iterations,&bool_fin);
	


	printf("\n\nbool_visualisation du main  =  %d\n",bool_visualisation );
	printf("\n\nindex_iteration du main  =  %d\n",index_iteration );
	printf("\n\nnb_iteration du main  =  %d\n",nb_iteration );
	printf("\n\nbool_fin du main  =  %d\n",bool_fin );
	return 0;
}
*/