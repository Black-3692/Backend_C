#include <string.h>
#include <stdlib.h>

#include "./request.h"

char *req_get_param(Request *req, const char *key) {
    if(req == NULL || key == NULL) {
        return NULL;
    }

    for(int i=0; i < req->params_count; i++) {
        if(strcmp(req->params[i].key, key) == 0) {
            return req->params[i].value;
        }
    }

    return NULL;
}

char *req_get_query(Request *req, const char *key) {
    if(req == NULL || key == NULL) {
        return NULL;
    }

    for(int i=0; i < req->query_count; i++) {
        if(strcmp(req->query[i].key, key) == 0) {
            return req->query[i].value;
        }
    }

    return NULL;
}

void free_request(Request *req) {
    if(req == NULL) {
        return;
    }

    free(req->body);

    for(int i=0; i < req->params_count; i++) {
        free(req->params[i].key);
        free(req->params[i].value);
    }

    free(req->params);

    for(int i=0; i < req->query_count; i++) {
         free(req->query[i].key);
         free(req->query[i].value);
    }

    free(req->query);

    free(req);
}
