#ifndef RESPONSE_H
#define RESPONSE_H

typedef struct {
    int client_socket;
} Response;

void send(Response *res, char *data);

#endif
