int comptage(char **matrice, char target, int indexLigne, int indexCol, int nbLig, int nbCol, int distance){
    int compteur = 0;
    
    int indexDebLig, indexDebCol, indexFinLig, indexFinCol;
    
    indexDebLig = indexLigne - distance;
    indexFinLig = indexLigne + distance;

    indexDebCol = indexCol - distance;
    indexFinCol = indexCol + distance;

    int i,j;

    /*printf("Index de fin %d, %d\n",indexFinLig,indexFinCol);*/

    //printf("Carac %c\n",target);

    for(i = indexDebLig; i <= indexFinLig; i++)
    {
        for(j = indexDebCol; j<=indexFinCol;j++)
        {
            //printf("Matrice[%d][%d] = %c\n",i,j,matrice[i][j]);
            //printf("Match ? %d\n",strcmp(&matrice[i][j],&target));
            if(j >= 0 && i >= 0 && i < nbLig && j < nbCol // Dans le cadre
                && matrice[i][j] == target) // Ça match.
            {                
                //if(i != indexLigne || j != indexCol)
                { // On ne compare la case du milieu)
                    //printf("Matrice[%d][%d] = %c\n",i,j,matrice[i][j]);
                    compteur++;
                } 
                
            }   
        }
    }

    if(target == matrice[indexLigne][indexCol]){compteur--;}

    /*printf("Compteur pour target : %c = %d\n",target,compteur);*/

    return compteur;
}