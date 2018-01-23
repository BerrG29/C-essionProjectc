//
// Created by ski on 23/01/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

#define MAX_BUFSIZE 2048

int writeFile(char *path, char *data) {
    FILE *fo;
    fo = fopen(path, "a");
    if(!fo) {
        return EXIT_FAILURE;
    }
    fputs(data, fo);
    fputs("\n\n", fo);
    fclose(fo);
    return EXIT_SUCCESS;
};

char *readFile(char *path, int n) {

    printf("\nn:%d\n", n);
    FILE *fo;
    fo = fopen(path, "r");
    if(!fo) {
        return NULL;
    }
    char *content = malloc(sizeof(char) * MAX_BUFSIZE);
    if (!content) {
        return NULL;
    }
    strcpy(content, "");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    int table_id = 0;
    int counter = 0; // to check if it's the next table
    while ((read = getline(&line, &len, fo)) != -1) {
        if (!strncmp(line, "\n", MAX_BUFSIZE)) {
            counter++;
        } else {
            counter = 0;
        }
        if (counter == 2) {
            table_id++;
            counter = 0;
        }
        if ((n == -1 || table_id == n) &&
            strncmp(line,"\n", MAX_BUFSIZE)) {
            strncat(content, line, MAX_BUFSIZE);
        }
    }
    free(line);
    fclose(fo);
    return content;
};