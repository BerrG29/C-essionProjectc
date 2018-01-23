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
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int cpt=0;
    char **matrix = (char **) malloc(sizeof(char *) * 100);
    int ligne;
    int colonne;
    int checkColumn;

    for (int j = 0 ; j < 100 ; j++)
    {
        matrix[j] = (char *) malloc(sizeof(char)*100);
    }


    int i;

    for (i = 1; i < argc; i++) {
	if (!strncmp(argv[i], "-m", MAX_INPUT_BUFSIZE)) {
		i++;
                line = NULL;
           	len = 0;
		cpt=0;
		ligne=0;
           	stream = fopen(argv[i], "r");
           	if (stream == NULL){
			printf("error to read provided file\n");
               		exit(EXIT_FAILURE);
		}
           	while ((read = getline(&line, &len, stream)) != -1) {
			if (ligne==0){
				checkColumn=read;			
			}
			if (read==checkColumn){
				cpt=0;
				while(cpt<read){
					matrix[ligne][cpt]=line[cpt];
					cpt++;			
				}
				ligne++;
			} else {
				printf("le contenu du fichier est incompatible avec l'application\n");			
			}
           	}

           	free(line);
           	fclose(stream);
		//printRes(matrix,cpt, ligne);
	} 
    }
    return EXIT_SUCCESS;
}


