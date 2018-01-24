#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int MAX_INPUT_BUFSIZE=256;

void printRes(char **matrix,int colonne,int ligne){
   //priting
   int i=0;
   int j=0;
   while(i<ligne-1) {
        while(j<colonne-1) {
	    printf("%c ", matrix[i][j]);
	    j++;
        }
	printf("\n");
	i++;
	j=0;
    }
}


int main(int argc, char *argv[])
{
    FILE *streamMatrix;
    FILE *streamMatrixRules;
    char *lineMatrix = NULL;
    char *lineMatrixRules = NULL;
    size_t len = 0;
    size_t read;
    int checkColumn;
    int mligne=0;
    int mcolonne=0;
    int rligne=0;
    int rcolonne=0;
    char **matrix=NULL;
    char **rules = NULL;

    for (int i = 1; i < argc; i++) {	
	if (!strncmp(argv[i], "-matrix", MAX_INPUT_BUFSIZE)) {
		streamMatrix = fopen(argv[i+1], "r");

		if (streamMatrix == NULL){
		    printf("error to read provided file\n");
		    exit(EXIT_FAILURE);
		}
		while ((read = getlineMatrix(&lineMatrix, &len, streamMatrix)) != -1) {
    
		    if (mligne==0){
			checkColumn=read;			
		    }
		    if (read==checkColumn){
			if (matrix == NULL){
				matrix=(char **) malloc(sizeof(char *));
			} else{
				matrix=(char **) realloc(matrix, (mligne + 1) * sizeof(char *));
			}

			if(matrix == NULL){
				exit(EXIT_FAILURE);
			}

			mcolonne=0;

			matrix[mligne]=(char *) malloc(sizeof(char)*read);
			if(matrix[mligne] == NULL){
				exit(EXIT_FAILURE);
			}
			while(mcolonne<read){
				matrix[mligne][mcolonne]=lineMatrix[mcolonne];
				mcolonne++;			
			}
			mligne++;
		    } else {
			printf("le contenu du fichier est incompatible avec l'application\n");			
		    }
		}
		free(lineMatrix);
		fclose(streamMatrix);
		printRes(matrix,mcolonne, mligne);
	}
	if (!strncmp(argv[i], "-rules", MAX_INPUT_BUFSIZE)){
		streamMatrixRules = fopen(argv[i+1], "r");

		if (streamMatrixRules == NULL){
		    printf("error to read provided file\n");
		    exit(EXIT_FAILURE);
		}
		while ((read = getlineMatrix(&lineMatrixRules, &len, streamMatrixRules)) != -1) {
		        
			if (!rules){
				rules=(char **) malloc(sizeof(char *));
			} else{
				rules=(char **) realloc(rules, (rligne + 1) * sizeof(char *));
			}

			rcolonne=0;
			//printf("Read column : %zu\n",read);
			//printf("allocation colonnes\n");
			rules[rligne]=(char *) malloc(sizeof(char)*read);
			while(rcolonne<read){
				rules[rligne][rcolonne]=lineMatrixRules[rcolonne];
				rcolonne++;			
			}
			rligne++;
		}
		free(lineMatrixRules);
		fclose(streamMatrixRules);
		printRes(rules,rcolonne, rligne);
	}
    }
    return EXIT_SUCCESS;
}



