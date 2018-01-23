//
// Created by ski on 22/01/18.
//
#include <string.h>
#include "client.h"
#include "thirdParty/mongoose/mongoose.h"

static int s_exit_flag = 0;
char *result = NULL;

static char *array2DtoArray(int x, int y, char data[x][y]) {
    char *res = malloc(sizeof(char*) * (x + 1) * y);
    if (!res) {
        return NULL;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            char tmp[1];
            sprintf(tmp, "%c", data[i][j]);
            strcat(res, tmp);
        }
        strcat(res, "\n");
    }
    return res;
}

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
        printf("ici: %s\n", res2);
    } else {
        printf("No results\n");
    }
    free(res2);

    /*
    printf("-------\n");
    char *res = client_get(argv[1]);
    if (res) {
        printf("%s", res);
    } else {
        printf("No results\n");
    }
    free(res);
*/

    return 0;
}
