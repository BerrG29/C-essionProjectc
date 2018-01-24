//
// Created by ski on 23/01/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "storage.h"

#define MAX_BUFSIZE 2048

/**
 * Function to create a folder (to store the data) if this file doesn't exist.
 * @param path
 */
static void check_folder(char *path) {
    struct stat st = {0};

    if (stat(DEFAULT_FOLDER, &st) == -1) {
        mkdir(DEFAULT_FOLDER, 0700);
    }
}

int writeFile(char *path, char *data, int isOdd) {

    if (!path) {
        return EXIT_FAILURE;
    }

    char _path[MAX_BUFSIZE];
    if (isOdd) {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_ODD);
    } else {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_PAIR);
    }

    check_folder(_path);

    FILE *fo;
    fo = fopen(_path, "a");
    if(!fo) {
        return EXIT_FAILURE;
    }

    fputs(data, fo);
    fputs("\n\n", fo);
    fclose(fo);
    return EXIT_SUCCESS;
};

int isCyclic(char *path, int isOdd) {
    if (!path) {
        return EXIT_FAILURE;
    }

    char _path[MAX_BUFSIZE];
    if (isOdd) {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_ODD);
    } else {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_PAIR);
    }

    FILE *fo;
    fo = fopen(_path, "r");
    if(!fo) {
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    char *content = malloc(sizeof(char) * MAX_BUFSIZE);
    char *content2 = malloc(sizeof(char) * MAX_BUFSIZE);
    if(!content || !content2) {
        return EXIT_FAILURE;
    }
    strcpy(content, "");
    strcpy(content2, "");
    int counter = 0; // to check if it's the next table
    while ((read = getline(&line, &len, fo)) != -1) {
        if (!strncmp(line, "\n", MAX_BUFSIZE)) {
            counter++;
        } else {
            if (counter == 2) {
                counter = 0;
                strcpy(content2, content);
                strcpy(content, "");
            }
            strncat(content, line, MAX_BUFSIZE);
        }
    }

    fclose(fo);
    if (!strcmp(content, content2)) {
        return 100;
    }
    return 101;
}

char *readFile(char *path, int n, int isOdd) {

    if (!path) {
        return EXIT_FAILURE;
    }

    char _path[MAX_BUFSIZE];
    if (isOdd) {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_ODD);
    } else {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_PAIR);
    }

    FILE *fo;
    fo = fopen(_path, "r");
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