#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function returning some rules requested by a user */
char condition() {

   char conditions[100][100];
   char newRule='d';
   int nbConditions;
   int cpt;
   int ligne=0;
   int colonne=0;
   
   while(newRule!='N'){
	 cpt=1;

         printf("Entrer un caractère :\n");
         scanf(" %c",&conditions[ligne][colonne]);
	 colonne++;

	 printf("Combien voulez vous de conditions?\n");
	 scanf("%d",&nbConditions);

	 while (cpt<=nbConditions){
		printf("Condition %d\n",cpt);
		printf("S'il y a au moins(-), au plus(+), aucun(0), exactement(=) ?\n");
		scanf(" %c",&conditions[ligne][colonne]);
		colonne++;
		if (conditions[ligne][colonne-1]=='-' || conditions[ligne][colonne-1]=='+'){
			printf("Combien?\n");
			scanf(" %c",&conditions[ligne][colonne]);
			colonne++;
		}
		printf("Caractère de type?\n");
		scanf(" %c",&conditions[ligne][colonne]);
		colonne++;
		printf("A quelle distance?\n");
		scanf(" %c",&conditions[ligne][colonne]);
		colonne++;
         	if (nbConditions-cpt>=1){
			printf("Structure logique entre les contitions? (& = ET/ | = OU)\n");
			scanf(" %c",&conditions[ligne][colonne]);
			colonne++;
		}
		conditions[ligne][colonne]='/';
		cpt++;
	 }
         printf("Voulez vous entrer une autre règle (O/N)?\n");
         scanf(" %c",&newRule);
	 ligne++;
	 colonne=0; 
   }
   conditions[ligne][colonne]='/';
   int i=0;
   int j=0;
 
   while(i!='/') {
        while(j!='/') {
            //printf(" %c", conditions[i][j]);
	    j++;
	    printf("%d ", j);
        }
	i++;
        printf("%d", i);
        printf("\n");
    }
   return conditions; 
}



int main(int argc, char *argv[])
{
    condition();
    return EXIT_SUCCESS;

}



