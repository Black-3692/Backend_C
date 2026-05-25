#ifndef SERVER_H
#define SERVER_H

#include "../context/context.h"
// Function used to create and start the server.
//
// port  -> Port number where the server will run.
//          Example: 8080
//
// queue -> Maximum number of client connections
//          waiting in the listen queue before accept().
//
// This function performs:
// 1. Socket creation
// 2. Binding IP and port
// 3. Listening for clients
// 4. Accepting client connections
void create_server(int port, int queue);

// Function used to read incoming data from the client socket.
//
// client_socket -> Connected socket returned by accept().
//
// This function reads the HTTP request
// sent by the client/browser.
void read_buffer(int client_socket, RequestContext *context);

#endif
