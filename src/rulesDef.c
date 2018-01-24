#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

/* function returning some rules requested by a user */
char **rules(int *nbRules) {

	int minimumValueInRule = 6;
	int nbCaseForEachCondition = 5;

   char newRule='d';
   int nbConditions;
   int cpt;
   int ligne=0;
   int colonne=0;
   //char **rules = (char **) malloc(sizeof(char *) * 100);
   char **rules; 
   rules = (char **) malloc(sizeof(char *)); // Pour une règle
    // for (int i = 0 ; i < 100 ; i++)
    // {
    //     rules[i] = (char *) malloc(sizeof(char)*100);
    // }
	// J'ai déplacé ce bloc dans "Combien de conditions ?".
   
   //new rule
   while(newRule!='N'){
		if(!rules){
			rules = (char **) malloc(sizeof(char *)); // Pour une règle
			rules[ligne] = (char *) malloc(sizeof(char)*minimumValueInRule);
		} else {
			rules = (char **) realloc(rules, sizeof(char *)); // Pour une nouvelle règle
			rules[ligne] = (char *) malloc(sizeof(char)*minimumValueInRule);
		}

		if(!rules){
			exit(EXIT_FAILURE);
		} 

	   *nbRules+= 1;
		char term;
		int nb;
		cpt=1;
        printf("Entrer un caractère :\n");
        scanf(" %c",&rules[ligne][colonne]);
	 while(rules[ligne][colonne]=='\n'){
 		printf("Ce caractère est interdit. Entrer un caractère?\n");
		scanf(" %c",&rules[ligne][colonne]);
 	 }
	 colonne++;

	 printf("Combien voulez vous de conditions?\n");
	 while(scanf("%d%c", &nbConditions, &term) != 2 || term != '\n'){
	 	printf("Merci d'entrer un entier.\n");
		scanf(" %c",&term);
		printf("Combien voulez vous de conditions?\n");
	 }

	if(nbConditions > 1){
		rules[ligne] = (char *)realloc(rules[ligne],nbCaseForEachCondition * nbConditions * sizeof(char));
		if(!rules[ligne]){
			exit(EXIT_FAILURE);
		}
	}
	

	 //new condition
	 while (cpt<=nbConditions){

		printf("Condition %d\n",cpt);
		
		printf("S'il y a au moins(-), au plus(+), aucun(0), exactement(=) ?\n");
		scanf(" %c",&rules[ligne][colonne]);
		while(rules[ligne][colonne]!='-' && rules[ligne][colonne]!='+' && rules[ligne][colonne]!='0' && rules[ligne][colonne]!='='){
	 		printf("Merci d'entrer moins(-), au plus(+), aucun(0), exactement(=)?\n");
			scanf(" %c",&rules[ligne][colonne]);
	 	}
		colonne++;

		if (rules[ligne][colonne-1]=='-' || rules[ligne][colonne-1]=='+' || rules[ligne][colonne-1]=='='){
			printf("Combien?\n");
			while(scanf("%d%c", &nb, &term) != 2 || term != '\n'){
	 			printf("Merci d'entrer un entier.\n");
				scanf(" %c",&term);
				printf("Combien?\n");
	 		}
			rules[ligne][colonne]=nb+'0';
			colonne++;
		}
		else{
			rules[ligne][colonne]='0';
			colonne++;
		}
		printf("Caractère de type?\n");
		scanf(" %c",&rules[ligne][colonne]);
		while(rules[ligne][colonne]=='\n'){
 			printf("Ce caractère est interdit. Caractère de type?\n");
			scanf(" %c",&rules[ligne][colonne]);
	 	}
		colonne++;

		printf("A quelle distance?\n");
		while(scanf("%d%c", &nb, &term) != 2 || term != '\n'){
	 		printf("Merci d'entrer un entier.\n");
			scanf(" %c",&term);
			printf("A quelle distance?\n");
 		}
		rules[ligne][colonne]=nb+'0';
		colonne++;

         	if (nbConditions-cpt>=1){
			printf("Structure logique entre les contitions? (& = ET / | = OU)\n");
			scanf(" %c",&rules[ligne][colonne]);
			while(rules[ligne][colonne]!='&' && rules[ligne][colonne]!='|'){
	 			printf("Merci d'entrer & = ET / | = OU?\n");
				scanf(" %c",&rules[ligne][colonne]);
	 		}
			colonne++;
		}
		cpt++;
	 }

	 printf("la case devient de type? \n");
	 scanf(" %c",&rules[ligne][colonne]);
         colonne++;
	 //rules[ligne][colonne]='\n';

         printf("Voulez vous entrer une autre règle (O/N)?\n");
         scanf(" %c",&newRule);

	 ligne++;
	 colonne=0; 
   }
   //rules[ligne][colonne]='\n';

   return rules; 
}

void printRes(char **rules){
   //priting
   int i=0;
   int j=0;
 
   while(rules[i][j]!='\n') {
        while(rules[i][j]!='\n') {
			printf("%c ", rules[i][j]);
			j++;
        }
		printf("\n");
		i++;
		j=0;
    }
}



