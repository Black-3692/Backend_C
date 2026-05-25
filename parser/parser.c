#include <stdio.h>
#include <string.h>

#include "./parser.h"

// Extracts HTTP method, path, and version
// from raw request buffer and stores into RequestContext.
//
void parse_buffer(char *buffer, RequestContext *context) {

    // Extract request line
    // Example:
    // GET /user HTTP/1.1
    sscanf(buffer, "%s %s %s", 
            context->method,
            context->path,
            context->version
    );
    
    // For now, body and query_string are empty
    context->body[0] = '\0';
    context->query_string[0] = '\0';
}
