#ifndef PARSER_H
#define PARSER_H

#include "../request/request.h"

Request *parser_request(char *raw_request);

#endif
