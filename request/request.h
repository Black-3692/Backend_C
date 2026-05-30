#ifndef REQUEST_H
#define REQUEST_H

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    char *body;

    KeyValue *params;
    int params_count;
    
    KeyValue *query;
    int query_count;
} Request;

char *get_req_param(Request *req, const char *key);

char *get_req_query(Request *req, const char *key);

void free_request(Request *req);

#endif
