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

/**
 * Allouer de la mémoire pour une matrice.
 */
char **allouerMemoireMemoire(int nbLig,int nbCol){
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

char **copierMatrice(char **matrice,int nbLig, int nbCol){
    char **mat = allouerMemoireMemoire(nbLig,nbCol);

    for(int i = 0 ; i < nbLig ; i++){
        for(int j = 0 ; j < nbCol ; j++){
            mat[i][j] = matrice[i][j];
        }
    }

    return mat;
}

char **initMatriceDeTest(){ 
    char ** matrice = allouerMemoireMemoire(4,4);
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

char *getOperateursLogique(char *regle){
    char *opLogique;

    printf("regle : %s\n",regle);

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