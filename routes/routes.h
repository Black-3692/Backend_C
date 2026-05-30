#ifndef ROUTES_H
#define ROUTES_H

#include "../context/context.h"
#include "../request/request.h"
#include "../response/response.h"

typedef void (*RouteHandler)(Request *res, Response *res);

typedef struct {

    char path[100]; 
    RouteHandler handler;
} Route;

void init_routes(int get_cap, int post_cap, int put_cap, int del_cap);

void get(char *path, RouteHandler handler);

void post(char *path, RouteHandler handler);

void put(char *path, RouteHandler handler);

void del(char *path, RouteHandler handler);

void handle_route(RequestContext *ctx);

#endif
