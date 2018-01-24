#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int nbL; int nbC; 
int x ; int y ; int idregle; int indiceLigne;
void Color(int couleurDuTexte,int couleurDeFond);
void initialisation(int nbL, int nbC,int **tableau, int **tab);
void saisieValue(int nbL, int nbC, int ** tableau, int ** tab, char * chainepaire, char * chaineimpaire);
void affichage(int nbL, int nbC, int **tableau, int **tab);
void regle(int x , int y, int idregle , int nbL, int nbC, int **tab);

void Color(int couleurDuTexte,int couleurDeFond) 
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
void initialisation(int nbL, int nbC,int ** tableau, int ** tab){
	int i,j;
	for(i=0; i<nbL; i++){
		for(j=0; j<nbC; j++){
			tab[i][j] = '0';
			tableau[i][i] = '0';
		}
	}
}
void saisieValue(int nbL, int nbC, int ** tableau, int ** tab, char * chainepaire, char * chaineimpaire){	
	int i; int indiceLigne = 0; char str1[80]; char str2[80];
    strcpy(str1, chainepaire);  strcpy(str2, chaineimpaire);
    char s[2] = "\n"; char *mot1; mot1 = strtok(str1, s);   
    while( mot1 != NULL ) {
		if (indiceLigne%2 == 0){
			for(i=0; i<nbL; i++){
				tableau[indiceLigne][i]= mot1[i];
			}
		}	
		else{
			for(i=0; i<nbL; i++){
				tab[indiceLigne-1][i]= mot1[i];
			}
		}
		indiceLigne = indiceLigne + 1; 
        mot1 = strtok(NULL, s);    
    }
    indiceLigne = 1;    char *mot2;     mot2 = strtok(str2, s); 
    while( mot2 != NULL ) {
		if (indiceLigne%2 != 0){
			for(i=0; i<nbL; i++){
				tableau[indiceLigne][i]= mot2[i];
			}
		}	
		else{
			for(i=0; i<nbL; i++){   
				tab[indiceLigne-1][i]= mot2[i];
			}
		}
		indiceLigne = indiceLigne + 1; 
        mot2 = strtok(NULL, s);   
    }
}
void regle(int x , int y, int idregle, int nbL, int nbC, int ** tab){
	tab[x][y] = idregle;
}
void affichage(int nbL, int nbC, int ** tableau, int ** tab){	
	int i,j;
	for(i=0; i<nbL; i++){
		for(j=0; j<nbC; j++){	
			if(tab[i][j] == 3 ){
				Color(9,0);	printf(" %c ", tableau[i][j]);
			}
			else if(tab[i][j] == 2){
				Color(12,0); printf(" %c ", tableau[i][j]);
			}
			else if(tab[i][j] == 6){
				Color(6,0); printf(" %c ", tableau[i][j]);
			}
			else{
				Color(15,0); printf(" %c ", tableau[i][j]);
			}	
		}
		printf("\n");
	}
	printf("\n");printf("\n");
}
int initialisationL(){
	int i = 0;
	printf("Veuillez entrer le nombre de Ligne \n");
    scanf("%4d", &i);
    return i;
}
int initialisationC(){
	int j = 0;
    printf("Veuillez entrer le nombre de Colone \n");
    scanf("%4d", &j);
    return j;
}
int main (int argc, char *argv[]){
	//nbL = initialisationL();
	//nbC = initialisationC();
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
	affichage(nbL, nbC, tableau, tab);
	printf(" Temps 1 \n");
	regle( 0, 1, 3, nbL, nbC, tab); regle( 0, 2, 3, nbL, nbC, tab); regle( 0, 3, 3, nbL, nbC, tab);
	regle( 1, 1, 3, nbL, nbC, tab); regle( 1, 2, 2, nbL, nbC, tab); regle( 1, 3, 3, nbL, nbC, tab);
	regle( 2, 1, 3, nbL, nbC, tab); regle( 2, 2, 3, nbL, nbC, tab); regle( 2, 3, 3, nbL, nbC, tab);
	affichage(nbL, nbC, tableau, tab);
	
	printf(" Temps 2 \n");
	char chainepaire2 [100]  = "XOOO\n0000\nXOOO\n0000";
	char chaineimpaire2 [100]= "XOXO\n0000\nXAXX\n0000";
	saisieValue(nbL, nbC, tableau, tab, chainepaire2, chaineimpaire2);
	affichage(nbL, nbC, tableau, tab);
	regle( 0, 0, 3, nbL, nbC, tab); 
	regle( 1, 0, 3, nbL, nbC, tab); regle( 1, 2, 3, nbL, nbC, tab);
	regle( 2, 0, 3, nbL, nbC, tab); 
	regle( 3, 0, 3, nbL, nbC, tab); regle( 3, 1, 6, nbL, nbC, tab); regle( 3, 2, 3, nbL, nbC, tab); regle( 3, 3, 3, nbL, nbC, tab);
	affichage(nbL, nbC, tableau, tab);
	
	printf(" Temps 3 \n");
	char chainepaire3   [100] = "OOOO\n0000\nOOOO\n0000";
	char chaineimpaire3 [100] = "OOOO\n0000\nOXOO\n0000";
	saisieValue(nbL, nbC, tableau, tab, chainepaire3, chaineimpaire3);
	affichage(nbL, nbC, tableau, tab);
	regle( 3, 1, 3, nbL, nbC, tab); 
	affichage(nbL, nbC, tableau, tab);
	
	printf(" Temps 4 \n");
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
