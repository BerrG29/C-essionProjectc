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