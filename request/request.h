#ifndef REQUEST_H
#define REQUEST_H

typedef struct {
    char method[10];
    char path[500];
    char body[1000];
} Request;

#endif
