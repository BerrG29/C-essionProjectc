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

char *client_get(char *url) {
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

char *client_post(char *url, char *data) {
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

int isCyclic(char *adr_server_odd, char *adr_server_pair) {

    char *m_odd = client_get(adr_server_odd);
    if (!m_odd) {
        return -1;
    }

    char *m_pair = client_get(adr_server_pair);
    if (!m_pair) {
        free(m_odd);
        return -1;
    }


    return -1;
}
char *matrix_is_stable(char *adr_server_odd, char *adr_server_pair) {

    char url[MAX_BUFSIZE] = {'\0',};
    snprintf(url, "%s/stable", adr_server_odd);
    int a = client_get(url);
    snprintf(url, "%s/stable", adr_server_pair);
    int b = client_get(url);

    if (a && b) {
        return 1;
    }

    return 0;
}

char *get_matrix_n_iteration(char *adr_server_odd, char *adr_server_pair, int n) {

    char *stable_url = "";
    char url[MAX_BUFSIZE] = {'\0',};
    snprintf(url, "%s?%d", adr_server_odd, n);
    char *m_odd= client_get(url);
    snprintf(url, "%s?%d", adr_server_pair, n);
    char *m_pair= client_get(url);

    // TODO Assembled the odd and pair lines to make one matrix
    return NULL;
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
/*
int main(int argc, char *argv[]) {

    int x = 5;
    int y = 5;
    int counter = 0;
    char data[5][5] = {0,};
    for (int i = 0 ; i < x; i++) {
        for (int j = 0; j < y; j++) {
            data[i][j] = 0x41 + counter;
            counter++;
        }
    }
    char *tmp = array2DtoArray(x, y, data);
    char *res2 = client_post(argv[1], tmp);

    if (res2) {
        printf("%s\n", res2);
    } else {
        printf("No results\n");
    }
    free(res2);
*/
/*
printf("-------\n");
char *res = client_get(argv[1]);
if (res) {
    printf("%s", res);
} else {
    printf("No results\n");
}
free(res);

return 0;
}

 */