#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include "appli.h"

const int nb_IP = 2;
const int length_IP = 20;

void printRes(char **matrix,int ligne,int colonne){
   //priting
   int i=0;
   int j=0;
   while(i<ligne) {
        while(j<colonne) {
			printf("%c", matrix[i][j]);
			j++;
        }
		printf("\n");
		i++;
		j=0;
    }
}

char **getDataMatrix(char *nameFile, int *mLigne, int *mColonne){
	char **matrix = NULL;
	FILE *streamMatrix = NULL;
	char *lineMatrix = NULL;

	size_t len = 0;
	size_t read;

	int ligne, colonne;
	ligne = *mLigne;
	colonne = *mColonne;

	int checkColumn=0;

	streamMatrix = fopen(nameFile, "r");
	if (streamMatrix == NULL){
		printf("error to read provided file\n");
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&lineMatrix, &len, streamMatrix)) != -1) {

		// Suppression du '\n' à recopier
		if(lineMatrix[read - 1] == '\n'){
			read -=1;
		}

		if (ligne==0){
			checkColumn=read;
		}
		if (read==checkColumn){
			if (matrix == NULL){
				matrix=(char **) malloc(sizeof(char *));
			} else{
				matrix=(char **) realloc(matrix, (ligne + 1) * sizeof(char *));
			}

			if(matrix == NULL){
				exit(EXIT_FAILURE);
			}

			colonne=0;

			matrix[ligne]=(char *) malloc(sizeof(char)*read);
			if(matrix[ligne] == NULL){
				exit(EXIT_FAILURE);
			}
			while(colonne<read){
				matrix[ligne][colonne]=lineMatrix[colonne];
				colonne+=1;			
			}
			ligne+=1;
		} else {
			printf("le contenu du fichier est incompatible avec l'application\n");			
		}
	}
	free(lineMatrix);
	fclose(streamMatrix);
	//printRes(matrix,*mColonne, *mLigne);

	printf("Ligne %d, colonne %d\n",ligne,colonne);

	*mLigne = ligne;
	*mColonne = colonne;

	printf("PointeurLigne %d, colonne %d\n",*mLigne,*mColonne);

	return matrix;
}

char **getRulesMatrix(char *nameFile, int *rLigne, int *rColonne){
	char **rules = NULL;
	FILE *streamRulesMatrix = NULL;
	char *lineRulesMatrix = NULL;

	int ligne, colonne;
	ligne = *rLigne;
	colonne = *rColonne;

	size_t len = 0;
	size_t read;

	streamRulesMatrix = fopen(nameFile, "r");
	if (streamRulesMatrix == NULL){
		printf("error to read provided file\n");
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&lineRulesMatrix, &len, streamRulesMatrix)) != -1) {
			
		if (!rules){
			rules=(char **) malloc(sizeof(char *));
		} else{
			rules=(char **) realloc(rules, (ligne + 1) * sizeof(char *));
		}

		if(lineRulesMatrix[read - 1] == '\n'){
			read -=1;
		}

		colonne=0;
		rules[ligne]=(char *) malloc(sizeof(char)*read);
		printf("Regle %d : ",ligne);
		while(colonne<read){
			printf("%c",lineRulesMatrix[colonne]);
			if(lineRulesMatrix[colonne] != '\n'){
				rules[ligne][colonne]=lineRulesMatrix[colonne];	
			}
			printf("%c",rules[ligne][colonne]);
			colonne+=1;			
		}
		printf("\n");
		ligne++;
	}
	free(lineRulesMatrix);
	fclose(streamRulesMatrix);
	//printRes(rules,*rColonne, *rLigne);

	printf("Ligne %d, colonne %d\n",ligne,colonne);

	*rLigne = ligne;
	*rColonne = colonne;

	printf("PointeurLigne %d, colonne %d\n",*rLigne,*rColonne);

	return rules;
}

char **getConfFile(char *nameFile){
	char **IPs = allouerMemoireMatrice(nb_IP,length_IP);
	
	
	FILE *streamFile = NULL;
	char *lineIP = NULL;

	size_t len = 0;
	size_t read;

	int colonne = 0, ligne = 0;

	streamFile = fopen(nameFile, "r");
	if (streamFile == NULL){
		printf("error to read provided file\n");
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&lineIP, &len, streamFile)) != -1) {
			
		colonne = 0;
		while(colonne<read){
			printf("%c",lineIP[colonne]);
			if(lineIP[colonne] != '\n'){
				IPs[ligne][colonne]=lineIP[colonne];	
			}
			colonne+=1;			
		}
		printf("\n");
		ligne++;

		// if(ligne == 0){
		// 	strncat(IP1,IPs[ligne],colonne);
		// } else if(ligne == 1){
		// 	strncat(IP2,IPs[ligne],colonne);
		// }

		printf("Ligne %d, colonne %d\n",ligne,colonne);
	}
	free(lineIP);
	fclose(streamFile);


	return IPs;
}