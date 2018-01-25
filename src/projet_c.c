#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "couleur.c"
#include "couleur.h"
#include "echequier.h"
#include "echequier.c"
#include <time.h>

void nomSimulation();

void nomSimulation(){

    time_t now = time (NULL);
    struct tm tm_now = *localtime (&now);
    strftime (s_now, sizeof s_now, "%d-%m-%Y-%H-%M-%S", &tm_now);
	strcat(simulation, s_now);
	printf("%s", simulation);
}

int main (int argc, char *argv[]){
	
	nomSimulation();
	printf ("\n");
	
	nbL=4; 
	nbC=4; 
	int i;   
	char **tableauDonnee; 
	int **tableauRegle;
	tableauDonnee = malloc(nbL * sizeof(*tableauDonnee)); 
	tableauRegle = malloc(nbL * sizeof(*tableauRegle));
	for(i=0 ; i < nbL ; i++){
		tableauDonnee[i] = malloc(nbC * sizeof(*(tableauDonnee[i])));
		tableauRegle[i] = malloc(nbC * sizeof(*(tableauRegle[i])));
	}
	
	printf(" Temps 0\n");
	initialisation(nbL, nbC, tableauDonnee, tableauRegle);
	
	char chainepaire1 [100]  = "XXXX\n0000\nXXXX\n0000";
	char chaineimpaire1 [100]= "XXOX\n0000\nXAXX\n0000";
	saisieValue(nbL, nbC, tableauDonnee, tableauRegle, chainepaire1, chaineimpaire1);
	
	regle( 0, 1, 3, nbL, nbC, tableauRegle); 
	regle( 0, 2, 3, nbL, nbC, tableauRegle); 
	regle( 0, 3, 3, nbL, nbC, tableauRegle);
	
	regle( 1, 1, 3, nbL, nbC, tableauRegle); 
	regle( 1, 2, 2, nbL, nbC, tableauRegle); 
	regle( 1, 3, 3, nbL, nbC, tableauRegle);
	
	regle( 2, 1, 3, nbL, nbC, tableauRegle); 
	regle( 2, 2, 3, nbL, nbC, tableauRegle); 
	regle( 2, 3, 3, nbL, nbC, tableauRegle);
	
	affichage(nbL, nbC, tableauDonnee, tableauRegle);
	
	printf(" Temps 1 \n");
	char chainepaire2 [100]  = "XOOO\n0000\nXOOO\n0000";
	char chaineimpaire2 [100]= "XOXO\n0000\nXAXX\n0000";
	saisieValue(nbL, nbC, tableauDonnee, tableauRegle, chainepaire2, chaineimpaire2);
	
	regle( 0, 0, 3, nbL, nbC, tableauRegle); 
	
	regle( 1, 0, 3, nbL, nbC, tableauRegle); 
	regle( 1, 2, 3, nbL, nbC, tableauRegle);
	
	regle( 2, 0, 3, nbL, nbC, tableauRegle); 
	
	regle( 3, 0, 3, nbL, nbC, tableauRegle); 
	regle( 3, 1, 6, nbL, nbC, tableauRegle); 
	regle( 3, 2, 3, nbL, nbC, tableauRegle); 
	regle( 3, 3, 3, nbL, nbC, tableauRegle);
	
	affichage(nbL, nbC, tableauDonnee, tableauRegle);
	
	printf(" Temps 2 \n");
	char chainepaire3   [100] = "OOOO\n0000\nOOOO\n0000";
	char chaineimpaire3 [100] = "OOOO\n0000\nOXOO\n0000";
	saisieValue(nbL, nbC, tableauDonnee, tableauRegle, chainepaire3, chaineimpaire3);
	regle( 3, 1, 3, nbL, nbC, tableauRegle); 
	affichage(nbL, nbC, tableauDonnee, tableauRegle);
	
	printf(" Temps 3 \n");
	char chainepaire4   [100] = "OOOO\n0000\nOOOO\n0000";
	char chaineimpaire4 [100] = "OOOO\n0000\nOOOO\n0000";
	saisieValue(nbL, nbC, tableauDonnee, tableauRegle, chainepaire4, chaineimpaire4);
	affichage(nbL, nbC, tableauDonnee, tableauRegle);
	
	for(i=0 ; i < nbL ; i++){ 
       free(tableauDonnee[i]); free(tableauRegle[i]);     
    }
    free(tableauDonnee);free(tableauRegle);
	return 0;
}
