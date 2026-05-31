#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./parser.h"

static void request_init(Request *request) {
    request->method = NULL;
    request->path = NULL;
    request->version = NULL;

    request->headers = NULL;
    request->body = NULL;

    request->params = NULL;
    request->params_count = 0;

    request->query = NULL;
    request->query_count = 0;
}

Request *parser_request(char *raw_request) {
    Request *request = malloc(sizeof(Request));

    if(request == NULL) {
        return NULL;
    }

    request_init(request);

    char *request_copy = strdup(raw_request);

    if(request_copy == NULL) {
        free(request_copy);
        free(request);
        return NULL;
    }

    char *line = strtok(request_copy, "\r\n");

    if(line == NULL) {
        free(request_copy);
        free(request);

        return NULL;
    }

    char *method = strtok(line, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, " ");

    if(method != NULL) {
        request->method = strdup(method);
    }

    if(path != NULL) {
        request->path = strdup(path);
    }

    if(version != NULL) {
        request->version = strdup(version);
    }

    free(request_copy);
    return request;
}
