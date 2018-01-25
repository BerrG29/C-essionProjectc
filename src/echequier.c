#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "echequier.h"

void initialisation(int nbL, int nbC,char ** tableauDonnee, int ** tableauRegle){
	int i,j;
	for(i=0; i<nbL; i++){
		for(j=0; j<nbC; j++){
			tableauRegle[i][j] = 0 ;
			tableauDonnee[i][i] = '0';
		}
	}
}

void saisieValue(int nbL, int nbC, char ** tableauDonnee, int ** tableauRegle, char * chainepaire, char * chaineimpaire){	
	int i; 
	int indiceLigne = 0; 
	char str1[120]; 
	char str2[120];
    strcpy(str1, chainepaire);  
    strcpy(str2, chaineimpaire);
    char s[2] = "\n"; 
    char *mot1; 
    mot1 = strtok(str1, s);   
    while( mot1 != NULL ) {
		if (indiceLigne%2 == 0){
			for(i=0; i<nbL; i++){
				tableauDonnee[indiceLigne][i]= mot1[i];
			}
		}	
		else{
			for(i=0; i<nbL; i++){
				tableauRegle[indiceLigne-1][i]= mot1[i];
			}
		}
		indiceLigne = indiceLigne + 1; 
        mot1 = strtok(NULL, s);    
    }
    indiceLigne = 1;    
    char *mot2;     
    mot2 = strtok(str2, s); 
    while( mot2 != NULL ) {
		if (indiceLigne%2 != 0){
			for(i=0; i<nbL; i++){
				tableauDonnee[indiceLigne][i]= mot2[i];
			}
		}	
		else{
			for(i=0; i<nbL; i++){   
				tableauRegle[indiceLigne-1][i]= mot2[i];
			}
		}
		indiceLigne = indiceLigne + 1; 
        mot2 = strtok(NULL, s);   
    }
}

void affichage(int nbL, int nbC, char ** tableauDonnee, int ** tab){	
	int i,j;
	for(i=0; i<nbL; i++){
		for(j=0; j<nbC; j++){
			if(tab[i][j] == 1 ){
				printf ("\e[31;1m %c \e[0m", tableauDonnee[i][j]);
			}
			else if(tab[i][j] == 2 ){
				printf ("\e[32;1m %c \e[0m", tableauDonnee[i][j]);
			}
			else if(tab[i][j] == 3 ){
				printf ("\e[33;1m %c \e[0m", tableauDonnee[i][j]);
			}	
			else if(tab[i][j] == 4 ){
				printf ("\e[34;1m %c \e[0m", tableauDonnee[i][j]);
			}
			else if(tab[i][j] == 5){
				printf ("\e[35;1m %c \e[0m", tableauDonnee[i][j]);
			}
			else if(tab[i][j] == 6){
				printf ("\e[36;1m %c \e[0m", tableauDonnee[i][j]);
			}
			else if(tab[i][j] == 7){
				printf ("\e[37;1m %c \e[0m", tableauDonnee[i][j]);
			}
			else{ 
				printf ("\e[30;1m %c \e[0m", tableauDonnee[i][j]);
			}	
		}
		printf("\n");
	}
	printf("\n");
}
