#ifndef PARSER_H
#define PARSER_H

typedef struct {
    int client_socket;

    char *method;
    char *path;
    char *version;

    char *headers;
    char *body;
} RequestContext;

RequestContext *parser_request(char *raw_request, int client_socket);

void free_request_contest(RequestContext *context);

#endif
