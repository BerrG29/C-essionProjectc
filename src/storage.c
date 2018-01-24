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
 */
static void check_folder() {
    struct stat st = {0};

    if (stat(DEFAULT_FOLDER, &st) == -1) {
        mkdir(DEFAULT_FOLDER, 0700);
    }
}

static char *init_path(char *path, int isOdd) {

    if (!path) {
        return NULL;
    }

    char *_path = malloc(sizeof(char) * MAX_BUFSIZE);
    if (!_path) {
        return NULL;
    }
    strcpy(_path, "");
    if (isOdd) {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_ODD);
    } else {
        snprintf(_path, MAX_BUFSIZE, "%s%s%s", DEFAULT_FOLDER, path, EXTENSION_PAIR);
    }

    check_folder();

    return _path;
}

int writeFile(char *path, char *data, int isOdd) {

    char *_path = init_path(path, isOdd);
    if (!_path) {
        return EXIT_FAILURE;
    }

    FILE *fo;
    fo = fopen(_path, "a");
    if(!fo) {
        return EXIT_FAILURE;
    }

    fputs(data, fo);
    fputs("\n\n", fo);
    fclose(fo);
    free(_path);
    return EXIT_SUCCESS;
};

int isStable(char *path, int isOdd) {

    char *_path = init_path(path, isOdd);
    if (!_path) {
        return EXIT_FAILURE;
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
    free(line);
    fclose(fo);
    free(_path);
    int res =strcmp(content, content2);
    free(content);
    free(content2);
    if (!res) {
        return 0;
    }
    return 1;
}

static char *compare(char *path, char *content, int n) {

    FILE *fo;
    fo = fopen(path, "r");
    if(!fo) {
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;
    char *data = malloc(sizeof(char) * MAX_BUFSIZE);
    if (!data) {
        fclose(fo);
        return -1;
    }

    char *res = malloc(sizeof(char) * MAX_BUFSIZE);
    if (!res) {
        fclose(fo);
        free(data);
    }
    strcpy(data, "");
    strcpy(res, "");
    int iteration_number = 0;
    int counter = 0; // to check if it's the next table
    while ((read = getline(&line, &len, fo)) != -1) {
        if (!strncmp(line, "\n", MAX_BUFSIZE)) {
            counter++;
        } else {
            if (counter == 2) {
                printf("%d\n%d\n%d\n%s\n%s\n", n, iteration_number, strcmp(data,content), data, content);
                if (n != iteration_number && !strcmp(data, content)) {
                    char tmp[5] = {'\0',};
                    sprintf(tmp, "%d_", iteration_number);
                    printf("iteration number: %d\n");
                    strcat(res, tmp);
                }
                counter = 0;
                iteration_number++;
                strcpy(data, "");
            }
            strncat(data, line, MAX_BUFSIZE);
        }
    }
    free(line);
    free(data);
    fclose(fo);
    return res;
}

char *isCyclic(char *path, int isOdd, int current_iteration) {

    char *_path = init_path(path, isOdd);
    if (!_path) {
        return EXIT_FAILURE;
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
    if(!content) {
        return EXIT_FAILURE;
    }
    strcpy(content, "");
    int iteration_number = 0;
    int counter = 0; // to check if it's the next table
    while ((read = getline(&line, &len, fo)) != -1) {
        if (!strncmp(line, "\n", MAX_BUFSIZE)) {
            counter++;
        } else {
            if (counter == 2) {
                counter = 0;
                iteration_number++;
                strcpy(content, "");
            }
            strncat(content, line, MAX_BUFSIZE);
        }
    }

    printf("content:\n%s\niteration_number:%d\n", content, iteration_number);
    char *res = compare(_path, content, iteration_number);

    free(line);
    fclose(fo);
    free(_path);
    free(content);
    return res;
}

char *readFile(char *path, int n, int isOdd) {

    char *_path = init_path(path, isOdd);
    if (!_path) {
        return EXIT_FAILURE;
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
    free(_path);
    return content;
};