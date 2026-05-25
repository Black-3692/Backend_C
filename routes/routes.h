#ifndef ROUTES_H
#define ROUTES_H

#include "../context/context.h"



/*
 * RouteHandler
 * -------------
 * Function pointer used for route handlers.
 */
typedef void (*RouteHandler)(RequestContext *ctx);



/*
 * Route
 * -----
 * Stores route information.
 */
typedef struct {

    // Route path
    char path[100];

    // Route handler function
    RouteHandler handler;

} Route;

// Initialize the size of the methods
void init_routes(int get_cap, int post_cap, int put_cap, int del_cap);

// Register GET route
void get(char *path, RouteHandler handler);

// Register POST route
void post(char *path, RouteHandler handler);

// Register PUT route
void put(char *path, RouteHandler handler);

// Register DELETE route
void del(char *path, RouteHandler handler);



/*
 * Matches incoming request with routes
 * and executes matching handler.
 */
void handle_route(RequestContext *ctx);

#endif
