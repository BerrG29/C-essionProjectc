const int PARAMETRES_DANS_CONDITIONS = 4;

/**
 * Compte le nombre de caractères autour de d'un caractère ciblé
 */
int comptage(char **matrice, char target, int indexLigne, int indexCol, int nbLig, int nbCol, int distance){
    int compteur = 0;
    
    int indexDebLig, indexDebCol, indexFinLig, indexFinCol;
    
    indexDebLig = indexLigne - distance;
    indexFinLig = indexLigne + distance;

    indexDebCol = indexCol - distance;
    indexFinCol = indexCol + distance;

    int i,j;

    for(i = indexDebLig; i <= indexFinLig; i++)
    {
        for(j = indexDebCol; j<=indexFinCol;j++)
        {
            if(j >= 0 && i >= 0 && i < nbLig && j < nbCol // Dans le cadre
                && matrice[i][j] == target) // Ça match.
            {                
                    compteur++;                
            }   
        }
    }

    if(target == matrice[indexLigne][indexCol]){compteur--;}

    return compteur;
}

void indiceChangement(char **indiceRegles, int indexRegle, int indiceLigne, int indiceColonne){
    indiceRegles[indexRegle][0] = indiceLigne;
    indiceRegles[indexRegle][1] = indiceColonne;
}


/**
 * Allouer de la mémoire pour une matrice.
 */
char **allouerMemoireMatrice(int nbLig,int nbCol){
    char ** mat = (char**) malloc(nbLig * sizeof(char *));

    for(int i = 0;i<nbLig;i++){
        mat[i] = (char *) malloc(nbCol * sizeof(char));
    }

    return mat;
}

/**
 * Désallouer la mémoire d'une matrice.
 */
void desallouerMemoireMatrice(char **matrice,int nbSousMatrice){
    for(int i=0;i < nbSousMatrice;i++){
        free(matrice[i]);
    }
    free(matrice);
}

/**
 * Désallouer la mémoire d'une matrice.
 */
void desallouerMemoireRegles(int **matrice,int nbSousMatrice){
    for(int i=0;i < nbSousMatrice;i++){
        free(matrice[i]);
    }
    free(matrice);
}

char **copierMatrice(char **matrice,int nbLig, int nbCol){
    char **mat = allouerMemoireMatrice(nbLig,nbCol);

    for(int i = 0 ; i < nbLig ; i++){
        for(int j = 0 ; j < nbCol ; j++){
            mat[i][j] = matrice[i][j];
        }
    }

    return mat;
}

char **initMatriceDeTest(int nbLig, int nbCol){ 
    char ** matrice = allouerMemoireMatrice(nbLig,nbCol);
    matrice[0][0] = 'X';
    matrice[0][1] = 'X';
    matrice[0][2] = 'X';
    matrice[0][3] = 'X';

    matrice[1][0] = 'X';
    matrice[1][1] = 'X';
    matrice[1][2] = 'O';
    matrice[1][3] = 'X';

    matrice[2][0] = 'X';
    matrice[2][1] = 'X';
    matrice[2][2] = 'X';
    matrice[2][3] = 'X';

    matrice[3][0] = 'X';
    matrice[3][1] = 'A';
    matrice[3][2] = 'X';
    matrice[3][3] = 'X';

    return matrice;
}

char **initMatriceDeTest2(int nbLig, int nbCol){ 
    char ** matrice = allouerMemoireMatrice(nbLig,nbCol);
    matrice[0][0] = 'O';
    matrice[0][1] = '/';
    matrice[0][2] = 'O';
    matrice[0][3] = '/';
    matrice[0][4] = 'O';
    matrice[0][5] = 'S';

    return matrice;
}

char **initMatriceDeTest3(int nbLig, int nbCol){ 
    char ** matrice = allouerMemoireMatrice(nbLig,nbCol);
    matrice[0][0] = 'X';
    matrice[0][1] = 'O';
    matrice[0][2] = 'X';
    matrice[0][3] = 'X';
    matrice[0][4] = 'O';
    matrice[0][5] = 'O';
    matrice[0][6] = 'A';

    matrice[1][0] = 'A';
    matrice[1][1] = 'O';
    matrice[1][2] = 'X';
    matrice[1][3] = 'A';
    matrice[1][4] = 'X';
    matrice[1][5] = 'X';
    matrice[1][6] = 'A';

    matrice[2][0] = 'A';
    matrice[2][1] = 'O';
    matrice[2][2] = 'X';
    matrice[2][3] = 'A';
    matrice[2][4] = 'O';
    matrice[2][5] = 'X';
    matrice[2][6] = 'A';

    matrice[3][0] = 'A';
    matrice[3][1] = 'O';
    matrice[3][2] = 'X';
    matrice[3][3] = 'O';
    matrice[3][4] = 'O';
    matrice[3][5] = 'O';
    matrice[3][6] = 'O';

    return matrice;
}

/**
 * Allouer de la mémoire pour une matrice.
 */
int **initMatriceRegles(int nbLig,int nbCol){
    int **mat = (int**) malloc(nbLig * sizeof(int *));

    for(int i = 0;i<nbLig;i++){
        mat[i] = (int *) malloc(nbCol * sizeof(int));
        for(int j=0;j <nbCol;j++){
            mat[i][j] = 0;
        }
    }
    return mat;
}

void reinitMatriceReglesAZero(int **matriceRules, int nbLig, int nbCol){
    for(int i=0; i<nbLig;i++){
        for(int j=0;j<nbCol; j++){
            matriceRules[i][j] = 0;
        }
    }
}

char getTarget(char *regle){
    return regle[0];
}

char getResult(char *regle){
    int len = strlen(regle);
    return regle[len-1];
}

char **getConditions(char *regle){
    char **conditions;

    int nbCondition = (int) strlen(regle)/5; 
    conditions = (char **) malloc(nbCondition * sizeof(char *));

    for(int i = 0; i<nbCondition; i++){
        conditions[i] = (char *) malloc(PARAMETRES_DANS_CONDITIONS * sizeof(char));
        conditions[i][0] = regle[1+i*5];
        conditions[i][1] = regle[2+i*5];
        conditions[i][2] = regle[3+i*5];
        conditions[i][3] = regle[4+i*5];
    }

    return conditions;
}

/**
 * Récupérer les signes logiques à tester par règle. ('au moins', 'au plus', ...)
 */
char* getLogiques(char *regle){
    int nbCondition = (int) strlen(regle)/5;
    char *logiques = (char *) malloc(nbCondition * sizeof(char));
    for(int i = 0; i < strlen(regle) ; i ++)
    {
        logiques[i] = regle[1+i*5];
    }

    return logiques;
}

/**
 * Récupérer le signe logique à tester par condition d'une règle. ('au moins', 'au plus', ...
 */
char getLogique(char *condition){
    return condition[0];
}

/**
 * Récupérer le nombre de caractères à compter autour des caractères à tester par règle. 
 */
int* getNbCaracteresACompter(char *regle){
    int nbCondition = (int) strlen(regle)/5;
    int *casesAutour = (int *) malloc(nbCondition * sizeof(int));
    for(int i = 0; i < strlen(regle) ; i ++)
    {
        casesAutour[i] = atoi(&regle[2+i*5]);
    }

    return casesAutour;
}

/**
 * Récupérer le nombre de caractères à compter autour d'un caractère par condition d'une règle. 
 */
int getNbCaractereACompter(char *condition){
    return atoi(&condition[1]);
}

/**
 * Récupérer les caractères à tester par règle.
 */
char* getCaracteresTest(char *regle){
    int nbCondition = (int) strlen(regle)/5;
    char *caracteresTest = (char *) malloc(nbCondition * sizeof(char));
    for(int i = 0; i < strlen(regle) ; i ++)
    {
        caracteresTest[i] = regle[3+i*5];
    }

    return caracteresTest;
}

/**
 * Récupérer le caractère à tester par condition d'une règle.
 */
char getCaractereTest(char *condition){
    return condition[2];
}

/**
 * Récupérer les distances à tester par règle.
 */
int* getDistances(char *regle){
    int nbCondition = (int) strlen(regle)/5;
    int *distances = (int *) malloc(nbCondition * sizeof(int));
    for(int i = 0; i < strlen(regle) ; i ++)
    {
        distances[i] = atoi(&regle[4+i*5]);
    }

    return distances;
}

/**
 * Récupérer la distance d'un caractère à tester par condition d'une règle.
 */
int getDistance(char *condition){
    return atoi(&condition[3]);
}

char *getOperateursLogiqueLiaison(char *regle){
    char *opLogique;

/*    printf("regle : %s\n",regle);*/

    int nbCondition = (int) strlen(regle)/5;
    if(nbCondition > 1){
        opLogique = (char *) malloc(nbCondition * sizeof(char));
        for(int i=0; i<nbCondition-1;i++) {
            opLogique[i] = regle[5+i*5];
        }
    }
    else {
        opLogique = '\0'; // Pointer null
    }

    return opLogique;
}

char getOperateurLogiqueLiaison(char *regle){
    return regle[6];
}

int getNBConditions(char *regle){

    int nbCondition;
    nbCondition = (int) strlen(regle)/5; 

    return nbCondition;
}

void iteration(char** matriceDeDonnees, char** matriceTemp, int** matriceRules, int nbLigne, int nbColonne, char **regles, int nbRegles)
{
    // char *caracteresTest;
	char **conditions;
	char *operateur;
	char target;
    char caractereTest;
	char resultat;
	
	int *cpt;
    int *nbCaracACompter;

	int nb_condi;
	int premiere_condi,deuxieme_condi;
    int distance;

    int indexRegle;

	for(int l=nbRegles - 1; l>=0;l--)
	{
        

		target = getTarget(regles[l]);
		conditions = getConditions(regles[l]);
		resultat = getResult(regles[l]);
		operateur = getOperateursLogiqueLiaison(regles[l]);
		nb_condi = getNBConditions(regles[l]);

        indexRegle = l+1;

		for(int i = 0;i< nbLigne;i++)
		{
			for(int j=0; j<nbColonne ; j++)
			{
				premiere_condi = 0;
				deuxieme_condi = 0;

				if(matriceDeDonnees[i][j] == target)
				{
					cpt = (int*) malloc(nb_condi * sizeof(int));
                    nbCaracACompter = (int*) malloc(nb_condi * sizeof(int));

					for(int k = 0; k<nb_condi; k++)
					{
                        caractereTest = getCaractereTest(conditions[k]);
                        distance = getDistance(conditions[k]);
                        cpt[k]= comptage(matriceDeDonnees,caractereTest, i, j,nbLigne,nbColonne,distance);
                        nbCaracACompter[k] = getNbCaractereACompter(conditions[k]);
					}

					if(nb_condi == 1)
					{
						if(regles[l][1] == '-' && cpt[0] >= nbCaracACompter[0])
						{
							matriceTemp[i][j]=resultat;
                            matriceRules[i][j] = indexRegle;           
						}
						else if(regles[l][1] == '+' && cpt[0] <= nbCaracACompter[0])
						{
							matriceTemp[i][j]=resultat;
                            matriceRules[i][j] = indexRegle;
						}
						else if(regles[l][1] == '0' && cpt[0] == 0)
						{
							matriceTemp[i][j]=resultat;
                            matriceRules[i][j] = indexRegle;
						}
						else if(regles[l][1] == '=' && cpt[0] == nbCaracACompter[0])
						{
							matriceTemp[i][j]=resultat;
                            matriceRules[i][j] = indexRegle;
						}
					}
					else
                    {
						/*
						Validation premiere condition
						*/

						if(regles[l][1] == '-' && cpt[0] >= nbCaracACompter[0])
						{
							premiere_condi=1;
						}
						else if(regles[l][1] == '+' && cpt[0] <= nbCaracACompter[0])
						{
							premiere_condi=1;
						}
						else if(regles[l][1] == '0' && cpt[0] == 0 )
						{
							premiere_condi=1;
						}
						else if(regles[l][1] == '=' && cpt[0] == nbCaracACompter[0])
						{
							premiere_condi=1;
						}

						/*
						Validation deuxième condition
						*/
						
						if(regles[l][6] == '-' && cpt[1] >= nbCaracACompter[1])
						{
							deuxieme_condi=1;
						}
						else if(regles[l][6] == '+' && cpt[1] <= nbCaracACompter[1])
						{
							
							deuxieme_condi=1;
						}
						else if(regles[l][6] == '0' && cpt[1] == 0 )
						{
							
							deuxieme_condi=1;
						}
						else if(regles[l][6] == '=' && cpt[1] == nbCaracACompter[1])
						{
							deuxieme_condi=1;
						}

						/*
						test sur les conditions 
						*/
						
						if(operateur[0] == '&' // Si l'opérateur logique est un &
							&& premiere_condi == 1 && deuxieme_condi == 1)
						{
                                matriceTemp[i][j]=resultat;
                                matriceRules[i][j] = indexRegle;                               
						}
						else if(operateur[0] == '|')
						{
							if(premiere_condi == 1 || deuxieme_condi == 1)
							{
                                matriceTemp[i][j]=resultat;
                                matriceRules[i][j] = indexRegle;
							}
						}
					}
                    free(cpt);
                    free(nbCaracACompter);
				}
			}
		}
        free(operateur);

        for(int d = 0;d < getNBConditions(regles[l]); d++){
            free(conditions[d]);
        }
        free(conditions);
	}

    for(int i = 0;i< nbLigne;i++){
        for(int j=0;j<nbColonne;j++){
            printf("%d",matriceRules[i][j]);
        }
        printf("\n");
    }
}
