#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

void dialogue(int *bool_visu, int *index_iteration, int *nb_iteration, int *nb_total){

	char ok;
	char term;
	int valid;


	printf("Voulez vous visualiser une itération particulière (O/N)?\n");
	scanf("%c%c", &ok, &term);

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
			printf("Quelle itération voulez vous visualiser ? entier entre (0 et %d)\n",*nb_total);
			}
			printf("index_iteration =  %d\n", *index_iteration);
		}

 	}
 	else if (ok == 'N')
 	{
 		*bool_visu = 0;

 	}
}


int main(int argc, char const *argv[])
{
	int bool_visualisation = 0;
	int index_iteration = 0;
	int nb_total_iterations = 0;
	int nb_iteration = 0;

	nb_total_iterations = 15;


	dialogue(&bool_visualisation,&index_iteration,&nb_iteration,&nb_total_iterations);
	


	printf("\n\nbool_visualisation du main  =  %d\n",bool_visualisation );
	printf("\n\nindex_iteration du main  =  %d\n",index_iteration );
	return 0;
}
