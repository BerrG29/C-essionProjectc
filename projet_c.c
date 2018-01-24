#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "couleur.c"
#include "couleur.h"
#include "echequier.h"
#include "echiquier.c"

int main (int argc, char *argv[]){
	
	nbL=4; nbC=4; int i;   
	int **tableau; int **tab;
	tableau = malloc(nbL * sizeof(*tableau)); tab = malloc(nbL * sizeof(*tab));
	for(i=0 ; i < nbL ; i++){
		tableau[i] = malloc(nbC * sizeof(*(tableau[i])));
		tab[i] = malloc(nbC * sizeof(*(tab[i])));
	}
	
	printf(" Temps 0\n");
	initialisation(nbL, nbC, tableau, tab);
	
	char chainepaire1 [100]  = "XXXX\n0000\nXXXX\n0000";
	char chaineimpaire1 [100]= "XXOX\n0000\nXAXX\n0000";
	saisieValue(nbL, nbC, tableau, tab, chainepaire1, chaineimpaire1);
	//affichage(nbL, nbC, tableau, tab);
	//printf(" Temps 1 \n");
	regle( 0, 1, 3, nbL, nbC, tab); regle( 0, 2, 3, nbL, nbC, tab); regle( 0, 3, 3, nbL, nbC, tab);
	regle( 1, 1, 3, nbL, nbC, tab); regle( 1, 2, 2, nbL, nbC, tab); regle( 1, 3, 3, nbL, nbC, tab);
	regle( 2, 1, 3, nbL, nbC, tab); regle( 2, 2, 3, nbL, nbC, tab); regle( 2, 3, 3, nbL, nbC, tab);
	affichage(nbL, nbC, tableau, tab);
	
	printf(" Temps 1 \n");
	char chainepaire2 [100]  = "XOOO\n0000\nXOOO\n0000";
	char chaineimpaire2 [100]= "XOXO\n0000\nXAXX\n0000";
	saisieValue(nbL, nbC, tableau, tab, chainepaire2, chaineimpaire2);
	//affichage(nbL, nbC, tableau, tab);
	regle( 0, 0, 3, nbL, nbC, tab); 
	regle( 1, 0, 3, nbL, nbC, tab); regle( 1, 2, 3, nbL, nbC, tab);
	regle( 2, 0, 3, nbL, nbC, tab); 
	regle( 3, 0, 3, nbL, nbC, tab); regle( 3, 1, 6, nbL, nbC, tab); regle( 3, 2, 3, nbL, nbC, tab); regle( 3, 3, 3, nbL, nbC, tab);
	affichage(nbL, nbC, tableau, tab);
	
	printf(" Temps 2 \n");
	char chainepaire3   [100] = "OOOO\n0000\nOOOO\n0000";
	char chaineimpaire3 [100] = "OOOO\n0000\nOXOO\n0000";
	saisieValue(nbL, nbC, tableau, tab, chainepaire3, chaineimpaire3);
	//affichage(nbL, nbC, tableau, tab);
	regle( 3, 1, 3, nbL, nbC, tab); 
	affichage(nbL, nbC, tableau, tab);
	
	printf(" Temps 3 \n");
	char chainepaire4   [100] = "OOOO\n0000\nOOOO\n0000";
	char chaineimpaire4 [100] = "OOOO\n0000\nOOOO\n0000";
	saisieValue(nbL, nbC, tableau, tab, chainepaire4, chaineimpaire4);
	affichage(nbL, nbC, tableau, tab);
	
	for(i=0 ; i < nbL ; i++){ 
       free(tableau[i]); free(tab[i]);     
    }
    free(tableau);free(tab);
	return 0;
}
