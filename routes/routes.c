#include <string.h>
#include <stdlib.h>

#include "./routes.h"

Route *get_routes = NULL;
Route *post_routes = NULL;
Route *put_routes = NULL;
Route *del_routes = NULL;

int get_capacity = 0;
int post_capicity = 0;
int put_capicity = 0;
int del_capicity = 0;

int get_count = 0;
int post_count = 0;
int put_count = 0;
int del_count = 0;

static void register_routes(Route **routes, int *count, int *capicity, const char *path, RouteHandler handler) {
    if(*count >= *capicity) {
        *capicity = (*capicity == 0) ? 4 : (*capicity * 2);
        
        Route *temp = realloc(*routes, sizeof(Route) * (*capicity));

        if(temp == NULL) {
            exit(EXIT_FAILURE);
        }
    
        *routes = temp;
    }

    (*routes)[*count].path = strdup(path);
    (*routes)[*count].handler = handler;

    (*count)++;
}

static Route *search_route(Route *routes, int count, const char *path) {
    for(int i=0; i < count; i++) {
        if(strcmp(routes[i].path, path) == 0) {
            return &routes[i];
        }
    }

    return NULL;
}

static Route *find_route(const char *method, const char *path) {
    if(strcmp(method, "GET") == 0) {
        return search_route (get_routes, get_count, path);
    }

    if(strcmp(method, "POST") == 0) {
        return search_route (post_routes, post_count, path);
    }

    if(strcmp(method, "PUT") == 0) {
        return search_route(put_routes, put_count, path);
    }

    if(strcmp(method, "DELETE") == 0) {
        return search_route(del_routes, del_count, path);
    }

    return NULL;
}

void get(const char *path, RouteHandler handler) {
    register_routes (
        &get_routes,
        &get_count,
        &get_capacity,
        path,
        handler
    );
}

void post(const char *path, RouteHandler handler) {
    register_routes (
        &post_routes,
        &post_count,
        &post_capicity,
        path,
        handler
    );
}

void put(const char *path, RouteHandler handler) {
    register_routes (
        &put_routes,
        &put_count,
        &put_capicity,
        path,
        handler
    );
}

void del(const char *path, RouteHandler handler) {
    register_routes (
        &del_routes,
        &del_count,
        &del_capicity,
        path,
        handler
    );
}

Route *find_routes(const char *method, const char *path) {
    return find_route(method, path);
}

void routes_cleanup(void) {
    int i;

    for(i=0; i < get_count; i++) {
        free(get_routes[i].path);
    }

    for(i=0; i < post_count; i++) {
        free(post_routes[i].path);
    }

    for(i=0; i < put_count; i++) {
        free(put_routes[i].path);
    }

    for(i=0; i < del_count; i++) {
        free(del_routes[i].path);
    }

    free(get_routes);
    free(post_routes);
    free(put_routes);
    free(del_routes);
} 
