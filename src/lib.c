const int PARAMETRES_DANS_CONDITIONS = 4;

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

    int nbCondition = (int) strlen(regle)/5; 
    if(nbCondition > 1){
        opLogique = (char *) malloc(nbCondition * sizeof(char));
        for(int i=0; i<nbCondition-1;i++) {
            opLogique[i] = regle[5+i*5];
        }
    }

    return opLogique;
}