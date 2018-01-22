//
// Created by ski on 22/01/18.
//
#include <string.h>
#include "client.h"
#include "thirdParty/mongoose/mongoose.h"

static int s_exit_flag = 0;
char *result = NULL;

static char *convertIntArrayToChar(int *data, int x, int y) {
    char *res = malloc(sizeof(char*) * (x + 1) * y);
    if (!res) {
        return NULL;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            char tmp[1];
            sprintf(tmp, "%c", data[i]);
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
    mg_mgr_free(&mgr);
    return result;
}

char *client_post(char *url, char *data) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);

    if (!url) {
        return NULL;
    }
//    mg_connect_http(&mgr, ev_handler, url, NULL, (char*)data);
    mg_connect_http(&mgr, ev_handler, url, NULL, (char*)data);

    while (s_exit_flag == 0) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    return result;
}

int main(int argc, char *argv[]) {

    import(argv[1]);
    printf("%s\n", result);

    printf("\n-------\n");

    int data[5][5];
    for (int i = 0 ; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            data[i][j] = 0x41 + i + j ;
        }
    }
    char * tmp = convertIntArrayToChar(&data, 5, 5);
    export(argv[1], tmp);
    printf("%s\n", result);
    free(result);
    return 0;
}
