/**
 * 
 * Pour lancer le traitement, il suffit d'exécuter : 
 * gcc -Wall traitement.c -o a.out && ./a.out
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "constantes.h"
#include "lib.c"
#include "appli.h"
#include "crypto.h"
#include "checkPass.h"
#include "rulesDef.c"
#include "client.h"
#include "dialPostTrait.h"
#include "echequier.h"
#include "couleur.h"

const int MAX_INPUT_BUFSIZE=256;

int main(int argc, char *argv[])
{
    // Variables interraction utilisateur post traitement
    int bool_visualisation = 0;
    int bool_fin = 0;
    int index_iteration = 0;
    int nb_total_iterations = 0;
    int nb_iteration = 0;

    char *nameFile = nomSimulation();

    char adr_server_odd[64] = "localhost:5000/";
    char adr_server_pair[64] = "localhost:5001/";

    char **matrice = NULL;
    char **matrice_tmp = NULL;
    char **regles = NULL;
    char **IPs = NULL;

    int **matriceForRules = NULL;
    int **matriceForRulesToDisplay = NULL;

    int nbLigne = 0, nbColonne = 0;
	int nbRegles = 0, rColonne = 0;

    int admin=0;
    //char filename[BUFSIZ]="./Documents/passwords.txt";

    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-admin", MAX_INPUT_BUFSIZE)) {
            admin=1;
            if( access(FILEPASSPATH, F_OK ) != -1 ) {
                if(checkPass()==1){
                crypto(); 
                    }
            } else {
            crypto();
            }

        }
        if (!strncmp(argv[i], "-conf", MAX_INPUT_BUFSIZE)) {
            if(checkPass()==1){
                IPs = getConfFile(argv[i+1]);
                //getConfFile(argv[i+1]);
                printf("Affichage IP\n");

                strcpy(adr_server_odd,IPs[0]);
                strcat(adr_server_odd,"/");
                strcpy(adr_server_pair,IPs[1]);
                strcat(adr_server_pair,"/");

                printf("IP %s\n",adr_server_odd);
                printf("IP %s\n",adr_server_pair);
            }
        }
		if (!strncmp(argv[i], "-matrix", MAX_INPUT_BUFSIZE)) {
			printf("Matrix : \n");
			matrice = getDataMatrix(argv[i+1],&nbLigne,&nbColonne);
			printRes(matrice,nbLigne,nbColonne);
            matrice_tmp = copierMatrice(matrice,nbLigne,nbColonne);
		}
		if (!strncmp(argv[i], "-rules", MAX_INPUT_BUFSIZE)){
			printf("Rules Matrix : \n");
			regles = getRulesMatrix(argv[i+1],&nbRegles,&rColonne);
			printRes(regles,nbRegles,rColonne);
			printf("\n");
		}
    }

    if (!admin){
        strcat(adr_server_odd,nameFile);
        strcat(adr_server_pair,nameFile);
        if(!matrice){
            printf("Vous n'avez pas matrice de données ou elle n'est pas valide");
            exit(EXIT_FAILURE);
        }
        
        if(!regles){
            regles = rules(&nbRegles,&nb_iteration);
        }

        if(!regles || !matrice){
            printf("Vous n'avez pas rentrée de règles");
            exit(EXIT_FAILURE);
        } else if(nb_iteration == 0){
            //TODO : Intégrer la partie avec l'entrée d'iterations
            char term;
            printf("Combien d'iteration souhaitez vous pour commencer?\n");     
            while(scanf("%d%c", &nb_iteration, &term) != 2 ){
                printf("Merci d'entrer un entier.\n");        
                printf("Combien d'iteration souhaitez vous pour commencer?\n");
                scanf(" %c",&term);
            }
        }

        
        // TRAITEMENT 

        // Écriture 

        // matrice = initMatriceDeTest(nbLigne,nbColonne);
        // matrice_tmp = initMatriceDeTest(nbLigne,nbColonne);
        matriceForRules = initMatriceRegles(nbLigne,nbColonne);
        matriceForRulesToDisplay = initMatriceRegles(nbLigne,nbColonne);

        // Fin écriture
        //printRes(regles);

        // Initialisation des regles
    /*
        printf("\n#-----------------------#\n");
        printf("#   Récupération règles #\n");
        printf("#-----------------------#\n\n");

        printf("Nombre de regles %d\n",nbRegles);
        for(int i = 0; i < nbRegles ; i ++){
            printf("Regle %d = ",i);
            for(int j = 0; j < strlen(regles[i]); j++){
                printf("%c",regles[i][j]);
            }
            printf("\n");
        }
    */
    /*    printf("Condition 1 : '%s'\n",regles[0]);
        printf("Condition 1 - 2 : '%c'\n",regles[0][1]);*/

        /*

        int nbConditions = 3,nbCaracteres = 11;
        regles = allouerMemoireMatrice(nbConditions,nbCaracteres);
        regles[0] = "X-1O1O";  
        regles[1] = "O=8X1X";
        regles[2] = "A-1X1&-1O1X";

        // regles[0] = "O-1/1A";  
        // regles[1] = "A05O2O";
        // regles[2] = "A+2A1$";

        // regles[0] = "X+2A2O";  
        // regles[1] = "O-3X1X";
        // regles[2] = "A=3X1&-2O2X";

        */

        printf("\n#-----------------------#\n");
        printf("#   Début traitement    #\n");
        printf("#-----------------------#\n\n");

        // Affichage matrice

        printf(" --- Affichage matrice  origine\n");
        for(int i=0; i<nbLigne; i++)
        {
            for(int j=0; j<nbColonne; j++)
            {
                printf("%c",matrice_tmp[i][j]);
            }
            printf("\n");
        }

        // Lancement

        
        //isCyclic(nbLigne, nbColonne, adr_server_odd, adr_server_pair);

        int compteur_cycle = 0;
        int cyclic = 1000;
        int stable;
        cyclic = send_matrix(nbLigne, nbColonne, matrice, adr_server_odd, adr_server_pair);
        while(bool_fin!=1)
        {
            if(bool_visualisation==0)
            {
                for(int f=0;f<nb_iteration;f++)
                {
                    printf("\nNEVER\n");
                    iteration(matrice,matrice_tmp,matriceForRules,nbLigne,nbColonne,regles,nbRegles);
                    desallouerMemoireMatrice(matrice,nbLigne);
                    matrice = copierMatrice(matrice_tmp,nbLigne,nbColonne);

                    // printf("Display adresse matrice : %p\n",matrice);
                    // printf("Display adresse matrice temp : %p\n",matrice_tmp);


                    stable = send_matrix(nbLigne, nbColonne, matrice, adr_server_odd, adr_server_pair);
                    /*    if(cyclic==0)
                    {
                    if(!stable) {
                        compteur_cycle++;
                    }
                    */
                    //affichage(nbLigne,nbColonne,matrice,matriceForRules);

                    /*   printf("cyclic %d\n", cyclic);
                    // TODO ici network

                    printf("\nTemps %d\n\n",f);*/
                    desallouerMemoireRegles(matriceForRulesToDisplay,nbLigne);
                    matriceForRulesToDisplay = copierMatriceRegles(matriceForRules,nbLigne,nbColonne);
                    printf("cyclic %d\n", cyclic);
                    // TODO ici network

                    printf("\nTemps %d\n\n",f);
                    reinitMatriceReglesAZero(matriceForRules,nbLigne,nbColonne);
                }

                nb_total_iterations+=nb_iteration;
                printf("Affichage matrice de l'itération %d\n\n\n\n",nb_total_iterations);
                // for(int i = 0;i< nbLigne;i++)
                // {
                //     for(int j=0;j<nbColonne;j++){
                //         printf("%c",matrice[i][j]);
                //     }
                //     printf("\n");
                // }

                affichage(nbLigne,nbColonne,matrice,matriceForRulesToDisplay);

                printf("\n");

            }
            else if(bool_visualisation == 1)
            {
                //TODO affichage matrice de l'itération index_iteration
            printf("affichage de la matrice de l'itération %d\n",index_iteration);
            }
            dialogue(&bool_visualisation,&index_iteration,&nb_iteration,&nb_total_iterations,&bool_fin);
        }

        printf("\n#-----------------------#\n");
        printf("#    Fin traitement     #\n");
        printf("#-----------------------#\n\n");

        // Désallocation de la mémoire

        desallouerMemoireMatrice(regles,nbRegles);

        desallouerMemoireMatrice(matrice,nbLigne);
        desallouerMemoireMatrice(matrice_tmp,nbLigne);
        // TODO : Désallouer la mémoire de la matrice for rules
        desallouerMemoireRegles(matriceForRules,nbRegles);
    }
    return 0;
}