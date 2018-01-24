void Color(int couleurDuTexte,int couleurDeFond) 
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void regle(int x , int y, int idregle, int nbL, int nbC, int ** tab){
	tab[x][y] = idregle;
}

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
