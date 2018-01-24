void Color(int couleurDuTexte,int couleurDeFond){
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void regle(int x , int y, int idregle, int nbL, int nbC, int ** tab){
	tab[x][y] = idregle;
}

//printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
//printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
//printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
//printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
//printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
//printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");

/*
int couleurRegle(int x, int y, int ** tab){
	int couleur = 15;
	if(tab[x][y] == 3 ){
		Color(9,0);
	}
	else if(tab[x][y] == 2){
		Color(12,0);
	}
	else if(tab[x][y] == 6){
		Color(6,0);
	}	
	return couleur;
}
*/
