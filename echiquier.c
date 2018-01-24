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

void affichage(int nbL, int nbC, int ** tableau, int ** tab){	
	int i,j;
	for(i=0; i<nbL; i++){
		for(j=0; j<nbC; j++){	
			if(tab[i][j] == 3 ){
				Color(9,0);	
				printf(" %c ", tableau[i][j]);
			}
			else if(tab[i][j] == 2){
				Color(12,0); 
				printf(" %c ", tableau[i][j]);
			}
			else if(tab[i][j] == 6){
				Color(6,0); 
				printf(" %c ", tableau[i][j]);
			}
			else{
				Color(15,0); 
				printf(" %c ", tableau[i][j]);
			}	
			//Color(couleurRegle(i, j, tab),0); printf(" %c ", tableau[i][j]);
		}
		printf("\n");
	}
	printf("\n");printf("\n");
}
