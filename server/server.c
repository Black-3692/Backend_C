#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "./server.h"

static Server server;

int server_init(int port, int queue_size) {
    server.port = port;
    server.queue_size = queue_size;
    server.is_running = 0;

    server.server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server.server_fd < 0) {
        perror("socket");
        return -1;
    }

    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(port);

    if(
            bind ( server.server_fd, 
                (struct sockaddr *)&server.address,
                sizeof(server.address)
            )  < 0
    ) {
        perror("bind");
        return -1;
    }

    if(
            listen(server.server_fd, queue_size) < 0
      )
    {
        perror("listen");
        return -1;
    }

    printf("Server listening on the port %d\n", port);

    return 0;
}

void server_start(void) {
    server.is_running = 1;
    printf("Starting the process of starting the server\n");
    while(server.is_running) {
        int client_socket;

        client_socket = accept(server.server_fd, NULL, NULL);
        if(client_socket < 0) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");
        close(client_socket);
    }
}
