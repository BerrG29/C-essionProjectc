//
// Created by ski on 22/01/18.
//

#include "lineModule.h"
#include "thirdParty/mongoose/mongoose.h"

static const char *s_http_port = "8000";

static const char *GET = "GET";
static const char *POST = "POST";

static void mg_printf_OK(struct mg_connection *nc, char *data) {
    mg_printf(nc,
              "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/plain\r\n"
                      "Content-Length: %d\r\n\r\n%s",
              (int) strlen(data), data);
}

static void mg_printf_not_implemented(struct mg_connection *nc) {
    mg_printf(nc, "%s",
              "HTTP/1.0 501 Not Implemented\r\n"
                      "Content-Length: 0\r\n\r\n");
}
/*
static void mg_printf_not_found(struct mg_connection *nc) {
    mg_printf(nc, "%s",
              "HTTP/1.1 404 Not Found\r\n"
                      "Content-Length: 0\r\n\r\n");
}
*/
static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (!strncmp(hm->method.p, GET, strlen(GET))) {
            char *data = "Get request\n";
            printf("%s\n", data);
            mg_printf_OK(nc, data);
        } else if (!strncmp(hm->method.p, POST, strlen(POST))) {
            char *data = "Post request\n";
            printf("%s\n%s\n", data, hm->body.p);
            mg_printf_OK(nc, data);
        } else {
            mg_printf_not_implemented(nc);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
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