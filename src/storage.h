//
// Created by ski on 23/01/18.
//

#ifndef C_ESSIONPROJECTC_STORAGE_H
#define C_ESSIONPROJECTC_STORAGE_H

#define DEFAULT_FOLDER "./dataLineModule/"
#define EXTENSION_ODD ".odd"
#define EXTENSION_PAIR ".pair"

/**
 * Create or update an existing table
 * @param path file concerned
 * @param data data to save in the file
 * @param is_odd 1 if the server saved the odd lines, else 0
 * @return EXIT_SUCCESS if the operation succeed, else return EXIT_FAILURE
 */
int writeFile(char *path, char *data, int is_odd);

/**
 * Function to check if the simulation reach a stable state or not
 * @param path file concerned
 * @param is_odd 1 if the server saved the odd lines, else 0
 * @return 1 if it's stable, else return 0
 */
int isStable(char *path, int is_odd);

/**
 *
 * @param path file concerned
 * @param n the n iteration wanted, if -1 return all, if n is not a number, return the first line
 * @param is_odd 1 if the server saved the odd lines, else 0
 * @return
 */
char *readFile(char *path, int n, int is_odd);

#endif //C_ESSIONPROJECTC_STORAGE_H
