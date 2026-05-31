#ifndef ROUTES_H
#define ROUTES_H

#include "../request/request.h"
#include "../response/response.h"

typedef void (*RouteHandler)(Request *req, Response *res);

typedef struct {
    char *path;
    RouteHandler handler;
} Route;

void get(const char *path, RouteHandler handler);
void post(const char *path, RouteHandler handler);
void put(const char *path, RouteHandler handler);
void del(const char *path, RouteHandler handler);

Route *find_routes(const char *method, const char *path);

void routes_cleanup(void);

#endif
