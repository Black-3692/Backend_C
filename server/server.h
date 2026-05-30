#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

typedef struct {
    int server_fd;
    int port;
    int queue_size;
    int is_running;

    struct sockaddr_in address;
} Server;

int server_init(int port, int queue_size);

void server_start(void);

void server_stop(void);

#endif
