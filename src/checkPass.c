#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>
#include "checkPass.h"


int checkPass(){
  char username[BUFSIZ], *password;  /* User input buffers         */
  char buf[BUFSIZ];                  /* File input buffer          */
  char *user_file, *pass_file;       /* Buffers for values in file */
  char filename[BUFSIZ]="./Documents/passwords.txt";             /* Filename buffer            */
  FILE *infile;                      /* File handle                */
  int res=0;
  
  printf("AUTHENTIFICATION : \n");

  /* Get the username from the user */
  printf("Username: ");
  scanf("%s", username);

  /* Get the password from the user */
  password = getpass("Password: ");

  /* Open the file */
  if((infile = fopen(filename, "r")) == NULL){

    printf("\nFile error!\nPlease init the pass file\n");

  } else {

  // lecture du fichier
  while (!feof(infile)) {

      buf[0] = '\0';

      fscanf(infile, "%s", buf);

      if(strlen(buf) == 0) continue;

      user_file = buf;

      pass_file = strchr(buf, ':');

      pass_file[0] = '\0';

      pass_file++;

      // regarder si le nom d'utilisateur
      if(strcmp(user_file, username) == 0){

        // regarder si le mot de pass match
        if(strcmp(crypt(password, pass_file), pass_file) == 0){

          printf("Correct password...\n");
	  res=1;

        } else {

          printf("Invalid user or password!\n");

        }
        break;
      } 
    }

    if(strcmp(user_file, username) != 0){
	printf("Invalid user or password!\n");
    }
    /* Close the file */
    fclose(infile);
  }
  return res;
}