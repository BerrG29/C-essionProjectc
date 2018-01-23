#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function returning some rules requested by a user */
char **rule() {

   //char conditions[100][100];
   char newRule='d';
   int nbConditions;
   int cpt;
   int ligne=0;
   int colonne=0;
   char **rules = (char **) malloc(sizeof(char *) * 100);/* ou malloc(L * sizeof *A); */
    for (int i = 0 ; i < 100 ; i++)
    {
        rules[i] = (char *) malloc(sizeof(char)*100);
    }
   
   //new rule
   while(newRule!='N'){
	 cpt=1;
	 char *p;
         printf("Entrer un caractère :\n");
	 //scanf("%c", p);
         scanf(" %c",&rules[ligne][colonne]);
	 colonne++;

	 printf("Combien voulez vous de conditions?\n");
	 scanf("%d",&nbConditions);

	 //new condition
	 while (cpt<=nbConditions){
		printf("Condition %d\n",cpt);
		printf("S'il y a au moins(-), au plus(+), aucun(0), exactement(=) ?\n");
		scanf(" %c",&rules[ligne][colonne]);
		colonne++;
		if (rules[ligne][colonne-1]=='-' || rules[ligne][colonne-1]=='+'){
			printf("Combien?\n");
			scanf(" %c",&rules[ligne][colonne]);
			colonne++;
		}
		printf("Caractère de type?\n");
		scanf(" %c",&rules[ligne][colonne]);
		colonne++;
		printf("A quelle distance?\n");
		scanf(" %c",&rules[ligne][colonne]);
		colonne++;
         	if (nbConditions-cpt>=1){
			printf("Structure logique entre les contitions? (& = ET / | = OU)\n");
			scanf(" %c",&rules[ligne][colonne]);
			colonne++;
		}
		cpt++;
	 }

	 printf("la case devient de type? \n");
	 scanf(" %c",&rules[ligne][colonne]);
         colonne++;
	 rules[ligne][colonne]='/';

         printf("Voulez vous entrer une autre règle (O/N)?\n");
         scanf(" %c",&newRule);

	 ligne++;
	 colonne=0; 
   }
   rules[ligne][colonne]='/';

   return rules; 
}

void printRes(char **rules){
   //priting
   int i=0;
   int j=0;
 
   while(rules[i][j]!='/') {
        while(rules[i][j]!='/') {
	    printf("%c ", rules[i][j]);
	    j++;
        }
	printf("\n");
	i++;
	j=0;
    }
}



//int main(int argc, char *argv[])
//{
//    printRes(rule());
//    return EXIT_SUCCESS;
//}



