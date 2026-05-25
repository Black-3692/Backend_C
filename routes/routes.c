#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./routes.h"

// Route table for each method
Route *get_routes = NULL;
Route *post_routes = NULL;
Route *put_routes = NULL;
Route *del_routes = NULL;

// Stored the number of registered routes
int get_count = 0;
int post_count = 0;
int put_count = 0;
int del_count = 0;

// Maximum route capicity
int get_capicity = 0;
int post_capicity = 0;
int put_capicity = 0;
int del_capicity = 0;

// Initializes the route tables
void init_routes(int get_cap, int post_cap, int put_cap, int del_cap) {
    get_capicity = get_cap;
    post_capicity = post_cap;
    put_capicity = put_cap;
    del_capicity = del_cap;

    get_routes = malloc(sizeof(Route) * get_capicity);
    post_routes = malloc(sizeof(Route) * post_capicity);
    put_routes = malloc(sizeof(Route) * put_capicity);
    del_routes = malloc(sizeof(Route) * del_capicity);
}

void get(char *path, RouteHandler handler) {
    // Preventing the route overflow
    if(get_count >= get_capicity) {
        printf("The limit exceeded for the get ...");
        return;
    }

    strcpy(get_routes[get_count].path, path);
    get_routes[get_count].handler = handler;
    get_count++;
}

void post(char *path, RouteHandler handler) {
    // Preventing the route overflow
    if(post_count >= post_capicity) {
        printf("The limit exceeded for the post ...");
        return;
    }

    strcpy(post_routes[post_count].path, path);
    post_routes[post_count].handler = handler;
    post_count++;
}

void put(char *path, RouteHandler handler) {
    // Preventing the route overflow
    if(put_count >= put_capicity) {
        printf("The limit exceeded for the put ...");
        return;
    }

    strcpy(put_routes[put_count].path, path);
    put_routes[put_count].handler = handler;
    post_count++;
}

void del(char *path, RouteHandler handler) {
    // Preventing the route overflow
    if(del_count >= del_capicity) {
        printf("The limit exceeded for the delete ...");
        return;
    }

    strcpy(del_routes[del_count].path, path);
    del_routes[del_count].handler = handler;
    del_count++;
}

void handle_route(RequestContext *context) {
    if(strcmp(context->method, "GET") == 0) {
        for(int i=0; i < get_count; i++) {
            if(strcmp(context->path, get_routes[i].path) == 0) {
                get_routes[i].handler(context);
                return;
            }
        }
    }

    if(strcmp(context->method, "POST") == 0) {
        for(int i=0; i < post_count; i++) {
            if(strcmp(context->path, post_routes[i].path) == 0) {
                post_routes[i].handler(context);
                return;
            }
        }
    }

    if(strcmp(context->method, "PUT") == 0) {
        for(int i=0; i < put_count; i++) {
            if(strcmp(context->path, put_routes[i].path) == 0) {
                put_routes[i].handler(context);
                return;
            }
        }
    }

    if(strcmp(context->method, "DELETE") == 0) {
        for(int i=0; i < del_count; i++) {
            if(strcmp(context->path, del_routes[i].path) == 0) {
                del_routes[i].handler(context);
                return;
            }
        }
    }

    printf("404 Route not found ...");
}
