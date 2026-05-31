#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

#include "./response.h"

#define MAX_RES_SIZE 8192

void res_status(Response *res, int status_code) {
    if(res == NULL) {
        return;
    }

    res->status_code = status_code;
}

static const char *get_status_text(int status_code) {
    switch(status_code) {
        case 200:
            return "Ok";

        case 201:
            return "Created";

        case 400:
            return "Bad Request";

        case 401:
            return "Unauthorized";

        case 404:
            return "Not Found";

        case 500:
            return "Internal Server Error";

        default:
            return "Ok";
    }
}

void res_send(Response *res, const char *content) {
    if(res == NULL || content == NULL) {
        return;
    }
    
    if(res->status_code == 0) {
        res->status_code = 200;
    }

    char response[MAX_RES_SIZE];

    int content_length = strlen(content);

    snprintf(
            response,
            sizeof(response),
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s",
            res->status_code,
            get_status_text(res->status_code),
            content_length,
            content
    );

    send(
            res->client_socket,
            response,
            strlen(response),
            0
        );
}
