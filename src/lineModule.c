//
// Created by ski on 22/01/18.
//

#include <string.h>
#include <stdlib.h>
#include "lineModule.h"
#include "storage.h"
#include "../thirdParty/mongoose/mongoose.h"

#define MAX_INPUT_BUFSIZE 256
#define DEFAULT_PORT "5000"
#define API_STABLE "/stable"
#define API_CYCLIC "/cyclic"

static const char *GET = "GET";
static const char *POST = "POST";

static int is_odd = 0; // 1 if it's true, else: 0

static void mg_printf_OK(struct mg_connection *nc, char *data) {
    mg_printf(nc,
              "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/plain\r\n"
                      "Content-Length: %d\r\n\r\n%s",
              (int) strlen(data), data);
}

static void mg_printf_created(struct mg_connection *nc) {
    mg_printf(nc,
              "HTTP/1.1 201 Created\r\n"
                      "Content-Length: 0\r\n\r\n");
}

static void mg_printf_not_implemented(struct mg_connection *nc) {
    mg_printf(nc, "%s",
              "HTTP/1.0 501 Not Implemented\r\n"
                      "Content-Length: 0\r\n\r\n");
}

static void mg_printf_not_found(struct mg_connection *nc) {
    mg_printf(nc, "%s",
              "HTTP/1.1 404 Not Found\r\n"
                      "Content-Length: 0\r\n\r\n");
}

/**
 *
 * @param uri
 * @param len
 * @return return the uri from the http_message, return NULL if an error happens
 */
static char *getUri(const char *uri, int len) {
    char *_uri = malloc(sizeof(char) * (len + sizeof(char)));
    if (!_uri) {
        return NULL;
    }

    strcpy(_uri, ".");
    strncat(_uri, uri, len);
    if (strstr(uri, "..")) {
        free(_uri);
        return NULL;
    }

    return _uri;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        char *uri = getUri(hm->uri.p, hm->uri.len);
        if (!uri) {
            mg_printf_not_implemented(nc);
        } else if (!strncmp(hm->method.p, GET, strlen(GET))) {
            char *query = strndup(hm->query_string.p, hm->query_string.len);
            if (!query) {
                mg_printf_not_found(nc);
            } else {
                const char *symbol = '/';
                char *ret = strrchr(uri, symbol);
                if (!strncmp(ret, API_STABLE, strlen(API_STABLE))) {
                    char *path = strndup(uri, strlen(uri) - strlen(ret));
                    int stable = isStable(path, is_odd);
                    char tmp[2];
                    sprintf(tmp, "%d", stable);
                    mg_printf_OK(nc, tmp);
                    free(path);
                } else if (!strncmp(ret, API_CYCLIC, strlen(API_CYCLIC))) {
                    char *path = strndup(uri, strlen(uri) - strlen(ret));
                    char *cyclic = isCyclic(path, is_odd);
                    if (cyclic) {
                        mg_printf_OK(nc, cyclic);
                        free(cyclic);
                    } else {
                        mg_printf_OK(nc, "-1");
                    }
                    free(path);
                } else {
                    int n = atoi(query);
                    char *res = readFile(uri, n, is_odd);
                    if (res) {
                        mg_printf_OK(nc, res);
                        free(res);
                    } else {
                        mg_printf_not_found(nc);
                    }
                }
            }
        } else if (!strncmp(hm->method.p, POST, strlen(POST))) {
            char *query_number = strndup(hm->query_string.p, hm->query_string.len);
            int n = atoi(query_number);
            free(query_number);
            char *query = strndup(hm->body.p, hm->body.len);
            if (!query) {
                mg_printf_not_found(nc);
            } else {
                writeFile(uri, query, is_odd);
                mg_printf_created(nc);
                free(query);
            }
        } else {
            mg_printf_not_implemented(nc);
        }
        free(uri);
    }
}

int main(int argc, char *argv[]) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    int port_length = 4;
    char *port = malloc(sizeof(char) * (port_length + 1));
    strcpy(port, DEFAULT_PORT);
    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "--port", MAX_INPUT_BUFSIZE) ||
            !strncmp(argv[i], "-p", MAX_INPUT_BUFSIZE)) {
            i++;
            if (!argv[i]) {
                printf("\nMissing options for %s\n", argv[i - 1]);
                return EXIT_FAILURE;
            }
            strncpy(port, argv[i], port_length);
        } else if (!strncmp(argv[i], "--odd", MAX_INPUT_BUFSIZE) ||
                   !strncmp(argv[i], "-o", MAX_INPUT_BUFSIZE)) {
            i++;
            if (!argv[i]) {
                printf("\nMissing options for %s\n", argv[i - 1]);
                return EXIT_FAILURE;
            }
            if (!strncmp(argv[i], "no", MAX_INPUT_BUFSIZE) ||
                !strncmp(argv[i], "n", MAX_INPUT_BUFSIZE)) {
                is_odd = 0;
            } else if  (!strncmp(argv[i], "yes", MAX_INPUT_BUFSIZE) ||
                        !strncmp(argv[i], "y", MAX_INPUT_BUFSIZE)) {
                is_odd = 1;
            } else {
                printf("\nError : port option\n");
                return EXIT_FAILURE;
            }
        } else if (!strncmp(argv[i], "--help", MAX_INPUT_BUFSIZE) ||
                   !strncmp(argv[i], "-p", MAX_INPUT_BUFSIZE)) {
            printf("lineModule - Webserver to save table\n"
                           "Syntax:\n"
                           "    lineModule [OPTIONS]\n"
                           "Options:\n"
                           "    -h, --help, Print this help\n"
                           "    -p, --port, Give the listening port to use\n"
                           "    -o, --odd,  Set the server in odd line mode [yes][no]\n"
            );
            return EXIT_SUCCESS;
        } else {
            printf("\nunknown options %s\n"
                           "usage: [--port port] [--odd yes/no]\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\nServer listen line odd %d\n", port, is_odd);
    nc = mg_bind(&mgr, port, ev_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}