#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>


int checkPass(){
  char username[BUFSIZ], *password;  /* User input buffers         */
  char buf[BUFSIZ];                  /* File input buffer          */
  char *user_file, *pass_file;       /* Buffers for values in file */
  char filename[BUFSIZ]="../Documents/passwords.txt";             /* Filename buffer            */
  FILE *infile;                      /* File handle                */
  int res=0;

  /* Get the username from the user */
  printf("Username: ");
  scanf("%s", username);

  /* Get the password from the user */
  password = getpass("Password: ");

  /* Open the file */
  if((infile = fopen(filename, "r")) == NULL){

    printf("\nFile error!\nAborting...\n");

  } else {

  /* Loop throught the file */
  while (!feof(infile)) {

      /* Initialize with empty string */
      buf[0] = '\0';

      /* Read in one line */
      fscanf(infile, "%s", buf);

      /* If it's an empty line, continue */
      if(strlen(buf) == 0) continue;

      /* Point to the buffer */
      user_file = buf;

      /* Point to the delimiter in the buffer */
      pass_file = strchr(buf, ':');

      /* Change the delimiter to a nul character */
      pass_file[0] = '\0';

      /* Move to the next character */
      pass_file++;

      /* See if this matches the name the user entered */
      if(strcmp(user_file, username) == 0){

        /* See if the passwords match */
        if(strcmp(crypt(password, pass_file), pass_file) == 0){

          printf("Correct password...\n");
	  res=1;

        } else {

          printf("Invalid user or password!\n");

        }
        break;

      } else {
	  printf("Invalid user or password!\n");
      } 

    }
  }

  /* Close the file */
  fclose(infile);
  return res;
}

int main(int argc, char **argv){
	int res=0;
	res=checkPass();
	printf("%d\n",res);
}
