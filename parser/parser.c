#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./parser.h"

RequestContext *parser_request(char *raw_request, int client_socket) {
    RequestContext *context = malloc(sizeof(RequestContext));

    if(context == NULL) {
        return NULL;
    }

    context->client_socket = client_socket;
    context->method = NULL;
    context->path = NULL;
    context->version = NULL;

    context->headers = NULL;
    context->body = NULL;

    char *request_copy = strdup(raw_request);

    if(request_copy == NULL) {
        free(request_copy);
        free(context);
        return NULL;
    }

    char *line = strtok(request_copy, "\r\n");

    if(line == NULL) {
        free(request_copy);
        free(context);

        return NULL;
    }

    char *method = strtok(line, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, " ");

    if(method != NULL) {
        context->method = strdup(method);
    }

    if(path != NULL) {
        context->path = strdup(path);
    }

    if(version != NULL) {
        context->version = strdup(version);
    }

    free(request_copy);
    return context;
}

void free_request_context(RequestContext *context) {
    free(context->method);
    free(context->path);
    free(context->version);

    free(context->headers);
    free(context->body);

    free(context);
}
