#ifndef CONTEXT_H
#define CONTEXT_H

/*
 * RequestContext
 * --------------
 * This structure represents a single HTTP request lifecycle.
 * It carries all request-related data from the server to parser,
 * middleware, router, and finally to the handler.
 */

typedef struct {

    /*
     * client_socket:
     * TCP socket descriptor for the connected client.
     * Used to read request data and send the response back.
     */
    int client_socket;

    /*
     * method:
     * HTTP method of the request (GET, POST, PUT, DELETE, etc.)
     */
    char method[16];

    /*
     * path:
     * Requested URL path (e.g., /user, /product)
     */
    char path[256];

    /*
     * version:
     * HTTP version (e.g., HTTP/1.1)
     */
    char version[16];

    /*
     * body:
     * Request payload/body data (used in POST/PUT requests).
     * Example: JSON, form data, etc.
     */
    char body[8192];

    /*
     * query_string:
     * URL query parameters extracted from the path.
     * Example: id=10&name=xxx
     */
    char query_string[512];

} RequestContext;

#endif
