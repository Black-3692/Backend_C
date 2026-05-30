#ifndef CONTEXT_H
#define CONTEXT_H

#include "../request/request.h"
#include "../response/response.h"

typedef struct {
    Request req;
    Response res;
} RequestContext;

#endif
