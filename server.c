#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "server.h"

// Function used to read the incoming data from the client socket.
// The client sends an HTTP request to the server.
// This function reads that request and stores it inside a buffer.
//
// client_socket - Socket returned by accept().
// It represents the connected client.
void read_buffer(int client_socket) {
    // Character array used to store incoming request data.
    // 4096 bytes means the server can read up to 4 KB of data at once.
    char buffer[4096];
    
    // read() is used to receive data from the client socket.
    //
    // client_socket       -> Connected client socket
    // buffer              -> Memory location where data is stored
    // sizeof(buffer) - 1  -> Maximum number of bytes to read
    //
    // We use -1 to leave space for '\0'
    // so the buffer can become a proper C string.
    int bytes = read(client_socket, buffer, sizeof(buffer) - 1);

    // If bytes > 0:
    // Data was successfully received from the client.
    if(bytes > 0) {
        // Add null character at the end of received data.
        // This converts raw bytes into a valid string.
        buffer[bytes] = '\0';

        // Paresing the buffer and getting the HTTP method and the Path
        parse_buffer(buffer);
    }
} 

// Function used to extract important information
// from the HTTP request buffer.
//
// buffer -> Contains the complete HTTP request
//           received from the client/browser.
//
// Example request:
//
// GET /users HTTP/1.1
// Host: localhost:8080
//
// This function extracts:
// 1. HTTP Method  -> GET, POST, PUT, DELETE
// 2. Route/Path   -> /, /users, /login
void parse_buffer(char *buffer) {

    // Stores the HTTP method.
    // Example: GET, POST
    char method[10];

    // Stores the requested route/path.
    // Example: /users
    char path[100];

    // sscanf() reads formatted data from the buffer.
    //
    // "%s %s":
    // First %s  -> Reads method
    // Second %s -> Reads path
    //
    // From:
    // GET /users HTTP/1.1
    //
    // It extracts:
    // method = GET
    // path = /users
    sscanf(buffer, "%s %s", method, path);

    // Print extracted HTTP method.
    printf("Method: %s\n", method);

    // Print extracted route/path.
    printf("Path: %s\n", path);
}

void create_server(int port, int queue) {
    // Server socket
    int server_socket;

    // Client socket
    int client_socket;

    // Server address
    struct sockaddr_in socket_address;

    // Creating server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET - It has the IPv4 address
    // SOCK_STREAM - Tells that tcp connection
    // 0 - represents the default protocol (TCP)

    if(server_socket < 0) {
        printf("Socket Creation Failed ...");
        return;
    }

    // Configure server
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;
    // sin_family - stores the IPv4 address
    // sin_port - stores the port
    // htons(port) - It is used to convert the integer into an network byte order
    // sin_addr - contains the IP address structure
    // s_addr - contains the actual IP address
    // INADDR_ANY - Accepts all the request from different IP
    // Later it will be modified
    
    // Bind socket
    int bind_check;

    bind_check = bind(server_socket, (struct sockaddr *)&socket_address, sizeof(socket_address));
    // bind - used to bind the IP address and then port

    if(bind_check < 0) {
        printf("Binding Failed ...");
        return;
    }

    // Listen to the port
    int listen_check;
    
    // listen - used to accept the clients connection
    listen_check = listen(server_socket, queue);
    
    if(listen_check < 0) {
        printf("Listining Failed ...");
        return;
    }

    printf("Server running on the port %d\n", port);
    printf("Queue size is %d\n", queue);

    // Infinite loop
    while(1) {
        // Accept client
        client_socket = accept(server_socket, NULL, NULL);

        if(client_socket < 0) {
            printf("Client connection failed ...");
            continue;
        }
       
        // Reading the buffer
        read_buffer(client_socket);

        // Closing the client socket
        close(client_socket);
    }
    
    // Closing the server socket
    close(server_socket);
}
