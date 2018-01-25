//
// Created by ski on 22/01/18.
//
#include <string.h>
#include "client.h"
#include "../thirdParty/mongoose/mongoose.h"

#define MAX_BUFSIZE 2048

static int s_exit_flag = 0;
char *result = NULL;

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_CONNECT:
            if (*(int *) ev_data != 0) {
                fprintf(stderr, "connect() failed: %s\n", strerror(*(int *) ev_data));
                s_exit_flag = 1;
            }
            break;
        case MG_EV_HTTP_REPLY:
            nc->flags |= MG_F_CLOSE_IMMEDIATELY;
            result = strndup(hm->body.p, hm->body.len);
            s_exit_flag = 1;
            break;
        case MG_EV_CLOSE:
            if (s_exit_flag == 0) {
                printf("Server closed connection\n");
                s_exit_flag = 1;
            }
            break;
        default:
            break;
    }
}

/**
 * Function to get a table saved on the remote server
 * @param url url of the remote server
 * @return
 */
static char *client_get(char *url) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    s_exit_flag = 0;
    if (!url) {
        return NULL;
    }

    mg_connect_http(&mgr, ev_handler, url, NULL, NULL);
    while (s_exit_flag == 0) {
        mg_mgr_poll(&mgr, 1000);
    }

    if (!result) {
        return NULL;
    }
    char *res = strdup(result);
    free(result);
    result = NULL;
    return res;
}

/**
 * Function to save a new table
 * @param url url of the remote server
 * @param data table to save
 * @return
 */
static char *client_post(char *url, char *data) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    s_exit_flag = 0;
    if (!url) {
        return NULL;
    }

    mg_connect_http(&mgr, ev_handler, url, NULL, (char*)data);

    while (s_exit_flag == 0) {
        mg_mgr_poll(&mgr, 1000);
    }

    if (!result) {
        return NULL;
    }

    char *res = strdup(result);
    free(result);
    result = NULL;
    return res;
}

// TODO Add a matrix to copy the rules
int send_matrix(int line_len, int column_len, char **matrix, char *adr_server_odd, char *adr_server_pair) {

    char *m_odd = malloc(sizeof(char*) * line_len * column_len);
    if (!m_odd) {
        return EXIT_FAILURE;
    }

    char *m_pair = malloc(sizeof(char*) * line_len * column_len);
    if (!m_pair) {
        free(m_odd);
        return EXIT_FAILURE;
    }

    strcpy(m_odd, "");
    strcpy(m_pair, "");
    char tmp[1];
    for (int i = 0; i < line_len; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < column_len; j++) {
                sprintf(tmp, "%c", matrix[i][j]);
                strcat(m_pair, tmp);
            }
            strcat(m_pair, "\n");
        } else {
            for (int j = 0; j < column_len; j++) {
                sprintf(tmp, "%c", matrix[i][j]);
                strcat(m_odd, tmp);
            }
            strcat(m_odd, "\n");
        }
    }

    int a = client_post(adr_server_odd, m_odd);
    int b = client_post(adr_server_pair, m_pair);
    free(m_pair);
    free(m_odd);
    if (a && b) {
        return 1;
    }

    return 0;
}

char **get_matrix_n_iteration(char *adr_server_odd, char *adr_server_pair, int n) {

    char *stable_url = "";
    char url[MAX_BUFSIZE] = {'\0',};
    sprintf(url, "%s?%d", adr_server_odd, n);
    char *m_odd= client_get(url);
    sprintf(url, "%s?%d", adr_server_pair, n);
    char *m_pair= client_get(url);

    // TODO Assembled the odd and pair lines to make one matrix
    return NULL;
}

int matrix_is_stable(char *adr_server_odd, char *adr_server_pair) {

    char url[MAX_BUFSIZE] = {'\0',};
    char *stable = "/stable";
    sprintf(url, "%s%s", adr_server_odd, stable);
    int a = client_get(url);
    sprintf(url, "%s%s", adr_server_pair, stable);
    int b = client_get(url);

    if (a && b) {
        return 1;
    }

    return 0;
}

int matrix_is_cyclic(char *adr_server_odd, char *adr_server_pair) {

    char url[MAX_BUFSIZE];
    char *cylic = "/cyclic";
    sprintf(url, "%s%s", adr_server_odd, cylic);
    char *iterations_odd = client_get(url);
    sprintf(url, "%s%s", adr_server_pair, cylic);
    char *iterations_pair = client_get(url);

    if (!strcmp(iterations_odd, "-1") || !strcmp(iterations_odd, "-1")) {
        return -1;
    }

    int *odd = malloc(sizeof(int));
    int *pair = malloc(sizeof(int));

    const char s[2] = "_";
    int i_odd = 0;
    char *token = strtok(iterations_odd, s);
    while (token != NULL) {
        odd = (int*)realloc(odd, (sizeof(int) * (i_odd + 1)));
        odd[i_odd] = atoi(token);
        i_odd++;
        token = strtok(NULL, s);
    }

    int i_pair = 0;
    token = strtok(iterations_pair, s);
    while (token) {
        pair = (int*)realloc(pair, sizeof(int) * (i_pair + 1));
        pair[i_pair] = atoi(token);
        i_pair++;
        token = strtok(NULL, s);
    }

    for (int i = 0; i < i_odd; i++) {
        for (int j = 0; j < i_pair; j++) {
            if (odd[i] == pair[j])
                return odd[i];
        }
    }

    return -1;
}
