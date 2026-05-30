#ifndef RESPONSE_H
#define RESPONSE_H

typedef struct {
    int client_socket;
    int status_code;
} Response;

void res_status(Response *res, int status_code);

void res_send(Response *res, const char *content);

#endif
